// FUNC_NAME: GodfatherGameManager::getCurrentState

extern void* g_globalManager; // DAT_01223514 - pointer to game manager singleton

int GodfatherGameManager::getCurrentState() {
    uint8_t requestType = 0; // identifies which data to retrieve (0 = current state)
    void* resultPtr = GameManagerInternal::resolveData(g_globalManager, &requestType); // FUN_005f0600
    if (resultPtr != nullptr) {
        return *static_cast<int*>(resultPtr);
    }
    return 0;
}