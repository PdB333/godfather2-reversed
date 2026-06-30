// FUNC_NAME: GodfatherGameManager::getInstance
GodfatherGameManager* GodfatherGameManager::getInstance() {
    // DAT_00e50b74 is a global pointer to the singleton instance
    return reinterpret_cast<GodfatherGameManager*>(g_pGodfatherGameManager);
}