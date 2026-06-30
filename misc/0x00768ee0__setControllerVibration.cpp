// FUNC_NAME: setControllerVibration
void setControllerVibration(int vibrationIntensity)
{
    // Retrieve the global InputManager singleton
    void* inputMgr = getInputManager(); // FUN_00471610
    if (inputMgr != nullptr) {
        // Offset +0x30 points to the controller slot (e.g., ControllerSlot)
        void* slot = reinterpret_cast<char*>(inputMgr) + 0x30;
        // Set vibration: intensity + default zeros for remaining motor/duration/type
        setSlotVibration(slot, vibrationIntensity, 0, 0, 0); // FUN_0054eb70
    }
}