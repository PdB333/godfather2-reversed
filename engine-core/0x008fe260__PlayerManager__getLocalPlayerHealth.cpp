// FUNC_NAME: PlayerManager::getLocalPlayerHealth
// Address: 0x008fe260
// Role: Returns the health (or some 4-byte field) of the local player, or 0 if no active player.

unsigned int getLocalPlayerHealth(void)
{
    // Get the singleton PlayerManager instance (assuming FUN_008fe1e0 is that)
    unsigned int playerMgr = PlayerManager::getInstance(); // FUN_008fe1e0

    // Fetch the local player object (FUN_006b0ee0 likely is PlayerManager::getLocalPlayer)
    int player = PlayerManager::getLocalPlayer(playerMgr); // FUN_006b0ee0

    if (player != 0) {
        // Return value at offset +0x48; guessed as Player::health
        // +0x48 might be an integer (health, ID, state flag)
        return *(unsigned int *)(player + 0x48);
    }
    return 0;
}