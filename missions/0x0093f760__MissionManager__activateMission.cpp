// FUNC_NAME: MissionManager::activateMission
// Address: 0x0093f760
// Role: Sets the active mission ID to 0x1194 and triggers mission start if global game state flags are set.

void __thiscall MissionManager::activateMission(MissionManager* this) {
    // Global game state pointer (DAT_01129c4c) - likely a singleton GameStateManager
    // Offsets: +0x48 = byte flag (e.g., isInGame), +0x5c = bitfield (e.g., flags & 1)
    if (*(char*)(g_pGameState + 0x48) != '\0' && (*(byte*)(g_pGameState + 0x5c) & 1) != 0) {
        // Set mission ID at offset +0x20 (e.g., m_activeMissionId)
        *(int*)(this + 0x20) = 0x1194; // Mission ID constant
        // Call mission start routine (FUN_0093a5c0)
        MissionManager::startMission();
    }
}