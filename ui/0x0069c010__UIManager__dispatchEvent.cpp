// FUNC_NAME: UIManager::dispatchEvent
void UIManager::dispatchEvent(void* thisPtr, uint eventData) {
    int iVar1;
    int handlerArray[3]; // stack buffer for handler info
    void (*handlerFunc)(); // function pointer to call

    // Begin event processing (e.g., push event context)
    beginEventProcessing(thisPtr);

    // Check if the system is active or if the event index is valid
    iVar1 = isSystemActive(); // FUN_00699ff0
    if ((iVar1 != 0) || ((-1 < g_currentEventIndex) && (g_currentEventIndex < (g_eventArrayEnd - g_eventArrayStart) >> 2))) {
        // Re-enter event context (maybe for nested events)
        beginEventProcessing(thisPtr);

        // Retrieve handler information for the given event data
        getEventHandler(handlerArray, eventData); // FUN_0069b510

        // If a handler was found, call it
        if (handlerArray[0] != 0) {
            handlerFunc = (void (*)())handlerArray[0];
            handlerFunc();
        }
    }
    return;
}