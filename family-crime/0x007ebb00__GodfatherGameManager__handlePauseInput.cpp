// FUNC_NAME: GodfatherGameManager::handlePauseInput
// Address: 0x007ebb00
// Role: Determines whether pause menu can be opened and handles pause input.
// Uses global game state checks and internal flags.

int __thiscall GodfatherGameManager::handlePauseInput(void) {
    char isGameActive;
    int result;

    isGameActive = isGameActive(); // FUN_007f47a0
    if (isGameActive != '\0' && ((*(uint*)(this + 0x24a0) >> 7 & 1) == 0)) {
        // Game is active and pause flag (bit 7) is not set
        if (isMultiplayer() == '\0') { // FUN_00481640
            result = openPauseMenu(this); // FUN_007eba50
            return result;
        }
    }
    // Either game not active, pause flag set, or multiplayer
    if (isMultiplayer() == '\0' || *(char*)(this + 0x241c) != '\0') {
        // Not multiplayer OR menu already open (byte at +0x241c non-zero)
        result = 0;
    } else {
        result = 1;
    }
    return result;
}