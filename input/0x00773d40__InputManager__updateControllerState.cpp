// FUNC_NAME: InputManager::updateControllerState
void __thiscall InputManager::updateControllerState(CControllerSlot* slot) {
    // slot is the 'this' pointer (param_1)
    // +0x5c: pointer to underlying device state (e.g., XINPUT_STATE)
    if (slot->deviceState != 0) {
        // Retrieve global input device manager singleton
        CInputDeviceManager* manager = (CInputDeviceManager*)FUN_0043b870(DAT_01131018);
        if (manager != 0) {
            // Call virtual function at vtable offset 0x38 (index 14)
            // Likely "isDeviceActive()" or "isConnected()"
            char isActive = manager->isDeviceActive();
            if (isActive != 0) {
                FUN_009aef10(); // Process active controller input
            }
        }
    }
}