// FUNC_NAME: InputController::clearOverride
// Function at 0x004305f0 - disables current input override and restores previous state
void InputController::clearOverride() {
    // Byte at +0x84: active flag
    *(uint8_t *)(this + 0x84) = 0;
    
    // Likely sets a timer or input delay (value 3)
    InputSystem::setOverrideTimer(3); // FUN_00609890
    
    // Save previous global override state
    int oldState1 = gOverrideToggle;      // DAT_011f38f0
    int oldState2 = gOverrideLock;        // DAT_011f38f4
    
    // Set current override value from this object
    gOverrideToggle = *(int *)(this + 0x80); // +0x80: m_overrideValue
    gOverrideLock = 0;
    
    // Restore the previous override state (with 0 as new action)
    InputSystem::applyOverrideState(0, oldState1, oldState2); // FUN_00609340
    
    // Check for pending active override
    bool wasActive = gOverrideActive; // DAT_011f38f8
    int  wasValue  = gOverrideValue;  // DAT_011f38fc
    gOverrideActive = false;
    gOverrideValue  = 0;
    
    // If there was an active override, notify the game manager
    if (wasActive || wasValue != 0) {
        // Virtual call at vtable+0x94 (likely InputManager::setOverrideActive(bool, bool))
        ((InputManager*)gInputManager)->setOverrideActive(true, false);
        // DAT_01205750 is a global InputManager instance
    }
}