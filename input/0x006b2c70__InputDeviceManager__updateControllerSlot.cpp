// FUNC_NAME: InputDeviceManager::updateControllerSlot
int __fastcall InputDeviceManager::updateControllerSlot(void* thisPtr) // ECX = thisPtr
{
    // +0x40: pointer to current controller device (e.g., XInput slot)
    setControllerDevice(*(void**)((char*)thisPtr + 0x40), 2); // set device type to XInput
    char xinputState[68]; // XINPUT_STATE (68 bytes)
    int success = readControllerState(xinputState); // non-zero if state read successfully
    if (success != 0) {
        setControllerConnected(1); // mark controller as connected
        processControllerInput(thisPtr); // handle state data
    }
    finalizeControllerUpdate(); // post-update cleanup
    return success;
}