// FUNC_NAME: GodfatherGameManager::setInstance
// Address: 0x00536940
// Role: Sets the global singleton instance pointer for GodfatherGameManager, and optionally triggers initialization if conditions are met.
void GodfatherGameManager::setInstance(void* pInstance) {
    // Store the given pointer into the global instance variable
    g_pGameManagerInstance = pInstance; // 0x0121a314

    // Check if the global pointer g_pSomePointer (0x012058e8) equals the address of g_SomeStaticMember (0x0121a1f0),
    // and if g_SomeValue (0x0121a204) equals g_AnotherValue (0x0121a35c),
    // and if g_SomeFlag (0x0121a330) is non-zero.
    if ((g_pSomePointer == &g_SomeStaticMember) &&
        (g_SomeValue == g_AnotherValue) &&
        (g_SomeFlag != 0)) {
        // If all conditions are met, call initialization function
        FUN_006063b0(); // Possibly GodfatherGameManager::initialize()
    }
}