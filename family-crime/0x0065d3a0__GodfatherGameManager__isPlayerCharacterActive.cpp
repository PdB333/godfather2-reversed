// FUNC_NAME: GodfatherGameManager::isPlayerCharacterActive
// Function address: 0x0065d3a0
// Checks if the local player's character is alive by traversing the game manager hierarchy.
// Returns 1 if alive, 0 otherwise.

int GodfatherGameManager::isPlayerCharacterActive() {
    GodfatherGameManager* gameMgr = (GodfatherGameManager*)FUN_00ad8d40(); // global singleton getter
    if (gameMgr) {
        // vtable+0x34: getPlayerManager()
        PlayerManager* playerMgr = gameMgr->getPlayerManager();
        if (playerMgr) {
            // vtable+0x24: getLocalPlayer()
            Player* player = playerMgr->getLocalPlayer();
            if (player) {
                // vtable+0x18: isAlive()
                return player->isAlive();
            }
        }
    }
    return 0;
}