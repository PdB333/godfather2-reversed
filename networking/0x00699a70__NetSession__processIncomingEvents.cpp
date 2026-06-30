// FUNC_NAME: NetSession::processIncomingEvents
undefined4 NetSession::processIncomingEvents(undefined4 param_1, undefined4 param_2) {
    char cVar1;
    int currentPtr;
    uint eventData[3];   // Buffer for event data (3 words)
    void (*eventHandler)(uint); // Function pointer for event handling

    currentPtr = DAT_01129f8c; // Start pointer of event list
    if (DAT_01129f8c != DAT_01129f90) { // If list not empty
        do {
            FUN_004d3bc0(param_1); // Pre-frame setup for session
            cVar1 = FUN_00699780(eventData, param_2); // Retrieve next event (returns true if terminating)
            if (eventData[0] != 0) {
                (*eventHandler)(eventData[0]); // Dispatch event
            }
            if (cVar1 != '\0') {
                return 1; // Indicate termination event occurred
            }
            currentPtr = currentPtr + 4; // Advance to next slot (each slot = 4 bytes)
        } while (currentPtr != DAT_01129f90);
    }
    return 0; // No termination event
}