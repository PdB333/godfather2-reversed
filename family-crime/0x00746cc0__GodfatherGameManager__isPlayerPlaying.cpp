// FUNC_NAME: GodfatherGameManager::isPlayerPlaying
// Address: 0x00746cc0
// Checks if the game currently has an active player session (e.g., player is not paused or disconnected).
// param_1 is a player object pointer (must be non-null to proceed).
bool GodfatherGameManager::isPlayerPlaying(void* playerPtr) {
    if (playerPtr == nullptr) {
        return false;
    }

    // Check if the global game manager (stored at DAT_01131064) is initialized and ready.
    if (FUN_0043b870(DAT_01131064) != 0) {
        // Retrieve the player manager singleton.
        int playerManager = FUN_00471610();
        // Examine the player manager's active flag at offset 0x30.
        // The flag is zero when the player is active (not paused/disconnected).
        if (*(char*)(playerManager + 0x30) == 0) {
            return true;
        }
    }
    return false;
}