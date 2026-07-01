// FUNC_NAME: GameManager::applyDefaultPlayerColor
// Address: 0x0094fb50
// GameManager casts: DAT_011298a0 -> gGameManager (GodfatherGameManager*)
// Player object retrieved via FUN_0079f9d0 (likely Player::getActivePlayer)
// Color bytes stored in global variables: DAT_011307b4 (R), DAT_011307b5 (G), DAT_011307b6 (B)
// Event hash 0x66d23fe5 likely corresponds to "PlayerColorSet" or similar.

int GameManager::applyDefaultPlayerColor() {
    // gGameManager is a global pointer to the singleton GodfatherGameManager
    // Offset +0x2c: m_bGameInitialized (byte flag)
    if (gGameManager->m_bGameInitialized == 0) {
        // Get the active Player instance
        Player* player = (Player*)FUN_0079f9d0();
        
        // Apply default color from global variables
        // Player offsets: +0x274 = m_colorR, +0x275 = m_colorG, +0x276 = m_colorB
        player->m_colorR = g_defaultColorR;   // DAT_011307b4
        player->m_colorG = g_defaultColorG;   // DAT_011307b5
        player->m_colorB = g_defaultColorB;   // DAT_011307b6
        
        // Notify systems of color change via a hashed event
        FUN_00894c90(0x66d23fe5);
        
        return 1;  // Color applied successfully
    }
    return 0;  // Game already initialized, color not applied
}