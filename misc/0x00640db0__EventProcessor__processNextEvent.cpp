// FUNC_NAME: EventProcessor::processNextEvent

// Address: 0x00640db0
// Handles the next event in the queue. Manages event shifting, state machine transitions,
// and error handling for unexpected event types.

#include <cstdint>

// Forward declarations
uint32_t getNextEvent(uint32_t* outData);                // FUN_00639c70
int32_t handleEvent(EventProcessor* this);               // FUN_0063fad0
void processGlobalEvents();                              // FUN_00643310
void advanceStateMachine(void* stateMachine);            // FUN_00642880
void sendAck(EventProcessor* this);                      // FUN_006417c0
void processDeferredEvents();                            // FUN_0063e400
char* formatString(const char* fmt, const char* arg);    // FUN_00636c00
void logError(const char* msg);                          // FUN_00638b80

class EventProcessor {
public:
    // Event type constants
    static const uint32_t kEventNone = 0x11f;            // 287 - no pending event
    static const uint32_t kEventProcessComplete = 0x112; // 274 - processing complete

    // Member fields (offsets relative to this):
    // +0x00: vtable pointer (implied)
    // +0x04: uint32_t m_lastEventId;          // previously processed event ID
    // +0x08: uint32_t m_nextEventId;          // event ID to be handled next
    // +0x0c: uint32_t m_activeEventId;        // currently active event ID
    // +0x10: uint32_t m_eventData;            // associated data for current event
    // +0x14: uint32_t m_queuedEventId;        // queued event ID (kEventNone if empty)
    // +0x18: uint32_t m_queuedEventParam;     // parameter for queued event
    // +0x1c: void* m_stateMachine;            // pointer to a state machine object

    void processNextEvent();
};

void __thiscall EventProcessor::processNextEvent(EventProcessor* this) {
    // Shift the last event ID into the next event slot
    this->m_nextEventId = this->m_lastEventId;

    // If there is no queued event, try to pop the next one from the global queue
    if (this->m_queuedEventId == kEventNone) {
        uint32_t newEvent = getNextEvent(&this->m_eventData);
        this->m_activeEventId = newEvent;
    } else {
        // Otherwise, dequeue the current queued event and shift the backup
        this->m_activeEventId = this->m_queuedEventId;
        this->m_eventData = this->m_queuedEventParam;
        this->m_queuedEventId = kEventNone;
    }

    // Dispatch the event to the handler
    int32_t status = handleEvent(this);

    // If the handler returns 1, change the status to 3 (likely "completed with acknowledgement")
    if (status == 1) {
        status = 3;
    }

    // Process any global events that may have been queued
    processGlobalEvents();

    // Advance the state machine
    void* sm = this->m_stateMachine;
    *(uint32_t*)((uint8_t*)sm + 0x1c) = *(uint32_t*)((uint8_t*)sm + 0x18); // copy next state
    advanceStateMachine(sm);

    // If the current event signals processing complete, handle a deferred queue
    if (this->m_activeEventId == kEventProcessComplete) {
        // Re‑initialize the event slot (same logic as above)
        this->m_nextEventId = this->m_lastEventId;
        if (this->m_queuedEventId == kEventNone) {
            uint32_t newEvent = getNextEvent(&this->m_eventData);
            this->m_activeEventId = newEvent;
        } else {
            this->m_activeEventId = this->m_queuedEventId;
            this->m_eventData = this->m_queuedEventParam;
            this->m_queuedEventId = kEventNone;
        }

        // Build a local event structure and push it onto the state machine's event stack
        void* sm = this->m_stateMachine;
        struct EventEntry {
            uint32_t eventId;                         // +0x00
            int32_t  nextIndex;                       // +0x04, -1 means end
            uint32_t param;                           // +0x08
            uint32_t flags;                           // +0x0c
            uint32_t padding;                         // +0x10
        };

        EventEntry localEntry; // on stack
        localEntry.eventId = *(uint32_t*)((uint8_t*)sm + 0x14);  // current event from state machine
        localEntry.nextIndex = -1;
        localEntry.param = *(uint32_t*)((uint8_t*)sm + 0x34);    // some parameter
        localEntry.flags = 0;
        localEntry.padding = 0;

        // Insert this entry as the new head of the event stack (linked list)
        *(EventEntry**)((uint8_t*)sm + 0x14) = &localEntry;

        // Send acknowledgement and handle deferred processing
        sendAck(this);
        processDeferredEvents();

        return;
    }

    // If the event is unexpected, trigger an assertion failure
    char* errorMsg = formatString("`%s' expected", (const char*)PTR_DAT_00e2a904); // error format
    logError(errorMsg);
    __debugbreak(); // swi(3) – breakpoint
}