// FUNC_NAME: PlayerManager::updateActivePlayerCount
void __fastcall PlayerManager::updateActivePlayerCount(int thisPtr)
{
    // Sum active player flags from 4 player slots (offsets: +0x30, +0x54, +0x78, +0x9c)
    uint activeCount = *(int *)(thisPtr + 0x30) + *(int *)(thisPtr + 0x54) + 
                       *(int *)(thisPtr + 0x78) + *(int *)(thisPtr + 0x9c);

    if (activeCount == 1) {
        // Exactly one active player
        FUN_0097baa0(); // e.g., handleSinglePlayer
        return;
    }
    if (activeCount > 1) {
        // Multiple active players
        FUN_0097e390(); // e.g., handleMultiPlayer
        return;
    }
    // No active players (activeCount == 0) – do nothing
    return;
}