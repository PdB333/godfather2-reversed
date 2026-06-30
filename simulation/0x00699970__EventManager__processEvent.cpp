// FUNC_NAME: EventManager::processEvent

// Reconstructed from Ghidra at 0x00699970
// This function iterates over a global array of event handler function pointers,
// calling each handler until one consumes the event.

// Globals: likely pointers to start and end of an array of handler function pointers
extern uint32_t g_pEventHandlerListStart; // DAT_01129f8c
extern uint32_t g_pEventHandlerListEnd;   // DAT_01129f90

// Forward declarations of helper functions (likely member functions of the same class)
extern void EventManager::resetHandlerState(); // FUN_004d3bc0
// Reads event data into buffer, returns non-zero if event was consumed
extern char EventManager::readEventToBuffer(uint32_t eventData[3], void* eventSource); // FUN_00699680

int __thiscall EventManager::processEvent(void* thisPtr, void* eventSource) {
    uint32_t currentPtr = g_pEventHandlerListStart;
    
    if (g_pEventHandlerListStart != g_pEventHandlerListEnd) {
        do {
            uint32_t eventData[3]; // local_10
            
            // Prepare/reset state before dispatching to each handler
            thisPtr->resetHandlerState();
            
            // Try to read an event; if consumed (cVar1 != 0), we stop processing
            char consumed = thisPtr->readEventToBuffer(eventData, eventSource);
            
            // If an event was extracted, call the current handler
            if (eventData[0] != 0) {
                // The current handler is a function pointer stored in the array at currentPtr
                void (*handler)(uint32_t) = *(void (**)(uint32_t))currentPtr;
                handler(eventData[0]);
            }
            
            // If any handler indicated the event was fully processed, return 1
            if (consumed != 0) {
                return 1;
            }
            
            // Advance to next handler pointer (4 bytes per pointer)
            currentPtr += 4;
        } while (currentPtr != g_pEventHandlerListEnd);
    }
    
    // No handler consumed the event
    return 0;
}