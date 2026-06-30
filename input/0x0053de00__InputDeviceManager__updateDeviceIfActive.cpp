// FUNC_NAME: InputDeviceManager::updateDeviceIfActive
void InputDeviceManager::updateDeviceIfActive(void)
{
    // Global device array: gDeviceArray (DAT_01198ec0), each entry 0x1b bytes
    // Global current device index: gCurrentDeviceIndex (DAT_0121bf30)
    // Check if the current device's active flag (offset +0x00) is non-zero
    if (gDeviceArray[gCurrentDeviceIndex].isActive != 0) {
        // Process the active device (calls FUN_006063b0)
        inputDeviceProcess();
    }
}