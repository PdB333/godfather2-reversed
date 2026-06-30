// FUNC_NAME: InputDeviceManager::notifyControllerReconnect
uint __thiscall InputDeviceManager::notifyControllerReconnect(void* thisPtr, uint param_2)
{
    int cmpResult;
    char isPaused;
    uint result;
    int mainLoopId;
    int currentMainLoopId;
    char isActive;
    char* reconnectString;
    char* formattedMessage;
    char* messageBuf;

    // If the controller slot index is 0x13 (19?) – possibly invalid or already handled
    if (*(char*)((int)thisPtr + 0x14) == '\x13') {
        // Get some hash/ID for this controller
        result = getControllerHash(0x10f05301, param_2);
        return result & 0xffffff00;
    }

    isPaused = isGamePaused();
    if (isPaused == '\0') {
        mainLoopId = *(int*)(DAT_0112980c + 4);          // Global main loop ID
        // Compare current main loop name with "GameMainLoop"
        int stringId = getString("GameMainLoop");
        currentMainLoopId = compareString(stringId);
        if (mainLoopId == currentMainLoopId) {
            isActive = isGameActive();
            reconnectString = "controller_reconnect_specific_paused";
            if (isActive == '\0') goto LAB_0068ccaf;
        }
    }
    reconnectString = "controller_reconnect_specific";

LAB_0068ccaf:
    // Format message: "{n:%d}{$%s}" with controller index+1 and reconnect string
    formatMessage(&messageBuf, 1, "{n:%d}{$%s}", (*(byte*)((int)thisPtr + 0x14) + 1), reconnectString);
    formattedMessage = messageBuf;
    if (messageBuf == (char*)0x0) {
        formattedMessage = &DAT_0120546e;                // Default empty string
    }

    // Send/push the formatted message
    pushMessage(param_2, formattedMessage);

    if (messageBuf != (char*)0x0) {
        // Deallocate the formatted message buffer
        messageBuf = (char*)(*local_4)(messageBuf);      // custom free function
    }

    return (uint)messageBuf & 0xffffff00;
}