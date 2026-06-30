// FUNC_NAME: InputDeviceManager::updateControllerSlot
undefined4 __thiscall InputDeviceManager::updateControllerSlot(int thisPtr, int controllerIndex)
{
    char connected;
    undefined4 result;
    int frameIndex;
    undefined4 extraOut_ECX;
    bool isSameIndex;
    undefined1 local_buffer[12];  // possibly a XINPUT_STATE or similar
    int storedIndex;
    undefined1 local_10;

    // Check if controller is connected
    connected = isControllerConnected(thisPtr, controllerIndex);
    if (connected != '\0') {
        return 1;
    }

    // Initialize or reset controller data
    initControllerData(thisPtr, thisPtr);

    // Check if the stored index matches the current one (maybe for a specific slot)
    isSameIndex = *(int *)(thisPtr + 0x18) == controllerIndex;

    // Get current frame or tick count
    frameIndex = getCurrentFrameIndex(extraOut_ECX);
    local_10 = isSameIndex;

    if (frameIndex >= 0) {
        // If frame index is valid, process normally
        result = getControllerState();
        storedIndex = controllerIndex;
        result = processControllerInput(thisPtr, result);
        return result;
    }

    // Otherwise, get a fallback state buffer
    getControllerState();
    storedIndex = controllerIndex;
    result = processControllerInput(thisPtr, local_buffer);

    // Clear a field related to last event timestamp or state
    *(undefined4 *)(thisPtr + 0x2f0) = 0;
    return result;
}