// FUNC_NAME: EventLoop::processEvents

// Reconstructed from Ghidra at 0x00903a50.
// Role: Event processing loop for the game's event queue.
// Handles three event types: data store, process/execute, and update.

#include <cstdint>

// Forward declarations of EA engine helper functions.
// 0x0043aff0: Initialize event monitor with a magic constant.
extern void __cdecl initEventMonitor(int param, uint32_t magic);
// 0x0043b120: Returns 1 if the event queue is empty, 0 otherwise.
extern bool __cdecl isEventQueueEmpty();
// 0x0043b210: Returns pointer to current event data (no argument).
// Overload: Copies current event data into provided buffer.
extern void* __cdecl getCurrentEvent();
extern void __cdecl getCurrentEvent(void* buffer);
// 0x0043ab70: Returns the type of the current event (0, 1, or 2).
extern int __cdecl getCurrentEventType();
// 0x0043ad10: Process an event from a local buffer.
extern void __cdecl processEvent(void* eventData);
// 0x0043b1a0: Advance to the next event (pop the queue).
extern void __cdecl advanceToNextEvent();

// Event types
enum EventType {
    EVENT_TYPE_DATA = 0,    // Store data from event into this->field_10
    EVENT_TYPE_PROCESS = 1, // Copy event to local buffer and process
    EVENT_TYPE_UPDATE = 2   // Update this->field_0 from event data
};

void __thiscall EventLoop::processEvents(short* this, int someParameter) {
    // Init with a magic timestamp/ID (0x23039dd0)
    initEventMonitor(someParameter, 0x23039dd0);

    // Loop while events are pending
    while (!isEventQueueEmpty()) {
        int eventType = getCurrentEventType();

        if (eventType == EVENT_TYPE_DATA) {
            // Event type 0: Extract a short from event offset +8 and store at this+20 (offset 10 words)
            void* eventData = getCurrentEvent();
            this[10] = *(short*)((uint8_t*)eventData + 8);
        }
        else if (eventType == EVENT_TYPE_PROCESS) {
            // Event type 1: Copy event into a local buffer at this+4 (offset 2 words) and process
            short* localBuffer = this + 2; // offset 4 bytes
            getCurrentEvent(localBuffer);
            processEvent(localBuffer);
        }
        else if (eventType == EVENT_TYPE_UPDATE) {
            // Event type 2: Update this->field_0 from event data
            void* eventData = getCurrentEvent();
            this[0] = *(short*)((uint8_t*)eventData + 8);
        }
        // Advance to the next event in the queue
        advanceToNextEvent();
    }
}