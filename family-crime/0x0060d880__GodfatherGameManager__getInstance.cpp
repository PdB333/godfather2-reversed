// FUNC_NAME: GodfatherGameManager::getInstance
// Address: 0x0060d880 - Returns global singleton pointer to GodfatherGameManager
GodfatherGameManager* GodfatherGameManager::getInstance()
{
    // Global pointer stored at DAT_012058a8, set during initialization
    return *DAT_012058a8;  // cast to pointer, assuming DAT_012058a8 is a GodfatherGameManager*
}