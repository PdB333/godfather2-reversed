// FUNC_NAME: EARSPlayer::spawnFromType
EARSPlayer* __thiscall EARSPlayer::spawnFromType(EARSPlayer* this) {
    int allocResult;
    EARSPlayer* player;

    // Check if this entity's type is 8 (likely "player" or "controller")
    if (*(short*)((char*)this + 0x22) == 8) {
        allocResult = (int)EARSAlloc(0x20); // Allocate 32 bytes for new player
        if (allocResult != 0) {
            if (g_currentPlayerIndex == 0) {
                player = EARSPlayer::create(0);
            } else {
                // Index into global array of player class IDs
                player = EARSPlayer::create(*(int*)((char*)g_playerClassIDs + g_currentPlayerIndex * 4));
            }
            return player;
        }
    }
    return 0;
}