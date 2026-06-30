// FUNC_NAME: GodfatherGameManager::isFeatureAllowed
// Address: 0x007120c0
// Role: Checks if a specific gameplay feature is currently allowed based on game state and a condition flag.

bool __fastcall GodfatherGameManager::isFeatureAllowed(int this) {
    char cVar1;
    int iVar3;

    // Dereference this+0x4 to get pointer to a sub-object (likely GameStateManager or similar)
    // then read offset 0x24c4 which is some state or flag (e.g., current game mode or enable flag)
    iVar3 = *(int *)(*(int *)(this + 0x4) + 0x24c4);

    // If the flag is 0 or 0x48 (specific values indicating disabled/invalid state), return false
    if (iVar3 == 0 || iVar3 == 0x48) {
        return false;
    }

    // Check if a global condition (like pause menu or cutscene) is active
    cVar1 = FUN_00718130(); // likely isInPauseOrCutscene() or similar
    if (cVar1 == '\0') {
        // No blocking condition, so check if the current game mode allows the feature
        iVar3 = FUN_00471610(); // returns current game state enum (e.g., eGameState)
        cVar1 = FUN_00718d40(iVar3 + 0x30); // check a bitmask or capability offset
        if (cVar1 == '\0') {
            return false;
        }
    }

    return true;
}