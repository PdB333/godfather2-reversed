// FUNC_NAME: EARSGameManager::~EARSGameManager
void __fastcall EARSGameManager::~EARSGameManager() {
    int iGlobalHandle;
    int *pAudioManager;
    bool bHasGlobalHandle;

    iGlobalHandle = s_pGlobalHandle;               // DAT_0120541c
    bHasGlobalHandle = (s_pGlobalHandle != 0);
    this->lpVtbl = &EARSGameManager_VTable_00e336c0; // set vtable to constructor table (maybe for safety)

    if (bHasGlobalHandle) {
        EARSGameManager::cleanupRenderResources();                  // FUN_00648b60
        EARSGameManager::cleanupAudioResources();                   // FUN_0064a740
        EARSGameManager::releaseGlobalHandle(iGlobalHandle);        // FUN_009c8eb0
    }
    s_pGlobalHandle = 0;

    pAudioManager = (int *)EARSGameManager::getAudioManager();     // FUN_009c8f80
    (*(void (**)(void))(*pAudioManager + 4))(s_pAudioManager, 0);  // call AudioManager::shutdown(0)
    s_pAudioManager = 0;                                            // DAT_01205410
    s_pAudioManagerRefCount = 0;                                    // DAT_01205414
    s_pAudioManagerSomething = 0;                                   // DAT_01205418

    if (this->m_pAllocatedMemory != 0) {                           // param_1[1] = this+4? but offset unclear
        EARSGameManager::freeAllocatedMemory(this->m_pAllocatedMemory); // FUN_009c8f10
    }

    this->lpVtbl = &EARSGameManager_VTable_00e336c4; // set vtable to destructor table
    s_pSomeGlobalFlag = 0;                                          // DAT_01223494
    return;
}