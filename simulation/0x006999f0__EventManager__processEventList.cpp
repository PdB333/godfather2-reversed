// FUNC_NAME: EventManager::processEventList
// Address: 0x006999f0
// Process a list of pending events by calling an update and checking for new events.
// Uses global pointers (DAT_01129f8c, DAT_01129f90) as a range of 4-byte slots.
// Returns 1 if an event was handled, 0 otherwise.

int EventManager::processEventList(uint thisPtr, uint param2) {
    void **startPtr = (void **)DAT_01129f8c;   // +0x01129f8c
    void **endPtr   = (void **)DAT_01129f90;   // +0x01129f90

    if (startPtr == endPtr) {
        return 0;
    }

    do {
        // Update per-slot state (likely internal manager update)
        FUN_004d3bc0(thisPtr);

        uint eventBuffer[3];   // buffer for event data
        bool hasEvent = FUN_00699700(eventBuffer, param2);

        if (eventBuffer[0] != 0) {
            // Decompiler shows (*local_4)(eventBuffer[0]) where local_4 is uninitialized.
            // Likely eventBuffer[0] holds a function pointer or object that should be invoked.
            // Hypothesize direct call:
            ((void (*)(uint))eventBuffer[0])(eventBuffer[0]);
        }

        if (hasEvent) {
            return 1;   // processed an event
        }

        startPtr++;   // advance by 4 bytes (next slot)
    } while (startPtr != endPtr);

    return 0;
}