// FUNC_NAME: EventManager::dispatchEvents
bool EventManager::dispatchEvents(void* thisPtr, void* eventContext) {
    // Global pointers to array of event listener function pointers (4 bytes each)
    uint* listenerStart = (uint*)gListenerArrayStart;      // DAT_01129f8c
    uint* listenerEnd   = (uint*)gListenerArrayEnd;        // DAT_01129f90

    if (listenerStart == listenerEnd) {
        return false;
    }

    do {
        // Prepare handler for processing (e.g., reset state)
        prepareHandler(thisPtr);  // FUN_004d3bc0

        // Get next event from the queue; returns true if a stop/done condition occurred
        uint eventData[3];  // local_10
        bool stopFlag = getNextEvent(eventData, eventContext);  // FUN_00699780

        // If event data is present, invoke the callback stored at the current listener slot
        if (eventData[0] != 0) {
            void (*callback)(uint) = (void (*)(uint))(*listenerStart);
            callback(eventData[0]);
        }

        if (stopFlag) {
            return true;
        }

        // Advance to next listener (4-byte step = pointer size)
        listenerStart++;
    } while (listenerStart != listenerEnd);

    return false;
}