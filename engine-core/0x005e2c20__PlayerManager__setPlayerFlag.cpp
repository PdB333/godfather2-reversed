// FUNC_NAME: PlayerManager::setPlayerFlag
bool PlayerManager::setPlayerFlag(uint flag)
{
    // Check if global debug/cheat flag is enabled (g_pGlobalConfig + 0x1744)
    if (*(char *)(g_pGlobalConfig + 0x1744) != '\0')
    {
        // Retrieve the local player object (FUN_005e2150)
        Player *pPlayer = getLocalPlayer();
        if (pPlayer != nullptr)
        {
            // Set the flag at offset 0x250 (e.g., m_playerFlags)
            pPlayer->m_playerFlags |= flag;
            return true;
        }
    }
    return false;
}