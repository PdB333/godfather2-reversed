// FUNC_NAME: GodfatherGameManager::getInstance
// Address: 0x008cd7a0
// Returns the singleton GodfatherGameManager instance.
GodfatherGameManager* GodfatherGameManager::getInstance()
{
    // Global pointer to the game manager (DAT_00e54550)
    return g_pGameManager;
}