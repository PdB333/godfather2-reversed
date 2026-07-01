// FUNC_NAME: Player::getHealthForMode
// Function address: 0x009185a0
// Returns the appropriate health value from the Player object based on the current game mode.
// The game mode is read from a global state object at DAT_01130044 + 0xb8.
// Damage/health fields are different for each mode (free roam, combat, stealth, etc.).

float __thiscall Player::getHealthForMode()
{
    int gameMode = *(int*)(g_globalState + 0xb8); // GameMode from global manager +0xb8

    // Mode 10, 11, 12: likely mission/free roam base health
    if (gameMode == 10 || gameMode == 11 || gameMode == 12)
        return *(float*)(this + 0x50); // baseHealth

    // Mode 25: likely combat health (e.g., during fight)
    if (gameMode == 25)
        return *(float*)(this + 0x5c); // combatHealth

    // Modes 13-17: likely stealth or special state health
    if (gameMode != 13 && gameMode != 14 && gameMode != 15 && gameMode != 16 && gameMode != 17)
    {
        // If not in any of the above modes, check another condition via auxiliary function
        if (isInAuxiliaryState()) // FUN_00917060 – e.g., in vehicle, taking cover, etc.
            return *(float*)(this + 0x74); // auxiliaryHealth
        else
            return 0.0f; // No valid health for current mode
    }

    // Modes 13-17: stealth health
    return *(float*)(this + 0x68); // stealthHealth
}