// FUNC_NAME: GameManager::SetLocalPlayerFlag
bool GameManager::SetLocalPlayerFlag(uint flag) {
    // Check if local player is active (global singleton +0x1744)
    if (g_pGameManager->m_bPlayerActive) {
        Player* pPlayer = g_pGameManager->GetLocalPlayer(); // calls FUN_005e2150
        if (pPlayer) {
            // Set flag at offset +0x250 (bitfield for player capabilities)
            pPlayer->m_playerFlags |= flag;
            return true;
        }
    }
    return false;
}