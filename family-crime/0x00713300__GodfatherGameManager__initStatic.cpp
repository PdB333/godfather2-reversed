// FUNC_NAME: GodfatherGameManager::initStatic
void GodfatherGameManager::initStatic(void)
{
    // Initialize the singleton GodfatherGameManager at global address 0x0112ac90
    GodfatherGameManager::initSingleton(&g_godfatherGameManager);
}