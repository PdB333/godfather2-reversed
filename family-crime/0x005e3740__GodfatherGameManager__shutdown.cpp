// FUNC_NAME: GodfatherGameManager::shutdown
// Function address: 0x005e3740
// Cleans up and shuts down various game subsystems. Called during application exit.
// param_1 is `this` pointer to GodfatherGameManager instance.

bool GodfatherGameManager::shutdown() {
    // Shutdown first subsystem (e.g., input manager, renderer)
    // g_pSomeManager is a global singleton pointer (DAT_01223514)
    Destroy(g_pSomeManager); // Release or clear? Called with no args?
    if (IsInitialized()) {
        // If initialized, zero out fields of g_pSomeManager
        g_pSomeManager[1] = 0; // Offset 0x4
        if (g_pSomeManager + 2 != nullptr) {
            g_pSomeManager[2] = 0; // Offset 0x8
            g_pSomeManager[3] = 0; // Offset 0xC
            *(int16_t*)(g_pSomeManager + 4) = 0; // Offset 0x10
            *(int16_t*)((int)g_pSomeManager + 0x12) = 0; // Offset 0x12
            Destroy(g_pSomeManager + 2, 0); // Release with a parameter
            ShutdownSubsystem(); // Some subsystem cleanup
        }
    }
    // Release g_pSomeManager object via vtable
    if (g_pSomeManager != nullptr) {
        (*(void(__thiscall*)(void*, int))g_pSomeManager[0])(g_pSomeManager, 1);
    }

    // Second global cleanup (e.g., audio manager)
    Destroy();

    // Check if networking subsystem is active
    if (g_bNetworkingInitialized != 0 && g_pNetworking != nullptr) {
        ShutdownNetworking();
    }

    // Shutdown various subsystems
    ShutdownAudio();      // 0x005f1cc0
    ShutdownInput();      // 0x005e1e50

    // Release another global pointer (e.g., renderer)
    if (g_pRenderer != nullptr) {
        (*(void(__thiscall*)(void*, int))g_pRenderer[0])(g_pRenderer, 1);
    }

    // Handle a large structure at g_pGameManager + 0x1804
    int* pStuff = g_pGameManager + 0x1804; // Offset 0x1804
    int* pBase = g_pGameManager;
    if (g_pGameManager[0x1804] != 0) {
        int* pTemp = g_pGameManager + 0x180f; // Offset 0x180f
        if (g_pGameManager[0x180f] != 0) {
            // Call virtual function at index 1 (release) on the object at offset 0x1804
            (*(void(__thiscall*)(void*, int))g_pGameManager[0x1804])(g_pGameManager[0x180f], 0);
            *pTemp = 0;
        }
        (*(void(__thiscall*)(void*))(*pStuff + 0xc))(); // Call virtual function at index 3
        pBase = g_pGameManager;
        *pStuff = 0;
    }

    // Release the main game manager object
    if (pBase != nullptr) {
        (*(void(__thiscall*)(void*, int))pBase[0])(pBase, 0);
        // Release the object at this->m_pSubObject (offset +4)
        if (this->m_pSubObject != nullptr) {
            (*(void(__thiscall*)(void*, int))this->m_pSubObject[0])(this->m_pSubObject, 0);
        }
    }

    // Shutdown additional subsystems
    ShutdownVFX();        // 0x005e7320
    if (g_pUIController != nullptr) {
        (*(void(__thiscall*)(void*, int))g_pUIController[0])(g_pUIController, 1);
    }
    ShutdownUI();         // 0x005dc1a0
    if (g_pSoundManager != nullptr) {
        (*(void(__thiscall*)(void*, int))g_pSoundManager[0])(g_pSoundManager, 1);
    }

    // Final call to a global object's vtable index 2
    (*(void(__thiscall*)(void*))g_pGlobalObject[2])(); // Call at index 2
    if (g_pGlobalObject != nullptr) {
        (*(void(__thiscall*)(void*, int))g_pGlobalObject[0])(g_pGlobalObject, 1);
    }

    // Release the sub-object stored at this+4
    if (this->m_pSubObject != nullptr) {
        (*(void(__thiscall*)(void*))this->m_pSubObject[2])(); // Call at index 2 (destructor?)
        this->m_pSubObject = nullptr;
        return true;
    }
    return false;
}