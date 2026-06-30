// FUNC_NAME: EventManager::dispatchEvent
void EventManager::dispatchEvent(int eventId, int eventData) {
    int iVar1;
    int callbackInfo[3]; // +0x00: callback function pointer, +0x04: user data, +0x08: flags
    void (*callbackFunc)(int); // uninitialized in decompilation, likely a member or global

    enterCriticalSection(this); // FUN_004d3bc0

    iVar1 = isProcessingAllowed(); // FUN_00699ff0

    // Check if event index is valid (global array bounds)
    if ((iVar1 != 0) || ((g_currentEventIndex >= 0) && (g_currentEventIndex < (g_eventArrayEnd - g_eventArrayStart) / 4))) {
        enterCriticalSection(this); // re-lock
        getEventHandler(callbackInfo, eventData); // FUN_0069b4b0

        if (callbackInfo[0] != 0) {
            // Call the stored callback function with the event data
            // Note: callbackFunc is uninitialized in decompilation; likely a member variable or global
            callbackFunc(callbackInfo[0]);
        }
    }
}