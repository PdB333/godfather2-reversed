// FUNC_NAME: InputManager::clearControllerButtonFlags
// Address: 0x005e2c60
// Description: Clears specified button flags on the active controller if the input system is enabled.
// Uses global singleton at 0x122350c (g_pInputManager).
// Offsets: +0x1744 = m_bEnabled (byte), +0x250 in controller object = m_buttonFlags (uint bitmask)

bool InputManager::clearControllerButtonFlags(uint buttonMask) {
    // Check if the input manager is enabled
    if (g_pInputManager->m_bEnabled != 0) {
        // Get the currently active controller state object
        ControllerState* pController = reinterpret_cast<ControllerState*>(FUN_005e2150());
        if (pController != nullptr) {
            // Clear the specified bits from the button flags
            pController->m_buttonFlags &= ~buttonMask;
            return true;
        }
    }
    return false;
}