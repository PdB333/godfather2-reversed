// FUNC_NAME: GodfatherGameManager::processDeferredEvent
// Function address: 0x005eb580
// Role: Processes one event from a deferred event queue. Returns true if the event was handled (callback invoked), false if cancelled or invalid.
// The event structure is passed as param_2. Fields: +0x8 = pointer to event data, +0xC and +0x10 = unknown (cleared after processing).

#include <cstdint>

// Forward declarations for callees
extern bool isPausedOrShuttingDown();       // FUN_005ec890 - checks if the system is in a state that should cancel deferred events
extern void cancelDeferredEvent(int* data); // FUN_005efca0 - cancels/frees deferred event data

// Structure representing a deferred event
struct DeferredEvent {
    int     field_0;        // +0x0 - unknown
    int     field_4;        // +0x4 - unknown
    int*    dataPtr;        // +0x8 - pointer to event-specific data
    int     field_c;        // +0xC - unknown, cleared after processing
    int     field_10;       // +0x10 - unknown, cleared after processing
};

// The class is assumed to be GodfatherGameManager (large offset at 0x81B8)
class GodfatherGameManager {
public:
    // Callback invoked to actually handle the deferred event's data.
    // Stored at offset 0x81B8 as a function pointer (void (*)(int*)).
    // In the original binary the decompiler shows a double indirection, but we simplify to a direct pointer.
    void (*m_eventCallback)(int*);   // +0x81B8

    // Public method: process a deferred event
    bool processDeferredEvent(DeferredEvent* event);
};

bool GodfatherGameManager::processDeferredEvent(DeferredEvent* event) {
    int* dataPtr = event->dataPtr;   // +0x8
    if (dataPtr == nullptr) {
        return false;               // No data to process
    }

    if (!isPausedOrShuttingDown()) {
        // System is active: invoke the callback if it's set
        if (this->m_eventCallback != nullptr) {
            this->m_eventCallback(dataPtr);
        }
        return true;                // Event was handled
    } else {
        // System is paused/shutting down: cancel the event data
        cancelDeferredEvent(dataPtr);
    }

    // Clear the deferred event fields (always performed)
    event->dataPtr = nullptr;
    event->field_c = 0;
    event->field_10 = 0;

    return false;                   // Event was cancelled or not processed
}