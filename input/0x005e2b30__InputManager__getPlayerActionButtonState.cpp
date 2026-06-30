// FUNC_NAME: InputManager::getPlayerActionButtonState
uint InputManager::getPlayerActionButtonState(uint param2) {
    // Check if the game is active (flag at offset 0x1744 in the global GameManager singleton)
    if (gGameManager->m_bGameActive != '\0') {
        // Retrieve the current player controller (e.g., from PlayerManager)
        uint playerController = getActivePlayerController();
        if (playerController != 0) {
            // Call the virtual method at vtable index 0x98 (method 38) on the input manager singleton.
            // The first argument is a field from the player controller at offset 0x1cc (likely an input state struct),
            // and the second argument is the caller's param2 (e.g., device index or action ID).
            // The result is a bitmask of pressed buttons.
            uint result = (*(**gInputManager)->vtbl[0x98 / 4])(
                *(uint *)(playerController + 0x1cc),
                param2
            );
            return result;
        }
    }
    // Fallback: return 0 with the low byte cleared (indicates no valid input)
    return 0xFFFFFF00;
}