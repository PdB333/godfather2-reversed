// FUNC_NAME: MainMenuManager::updateMenuState
void __thiscall MainMenuManager::updateMenuState(void *newState) {
    if (!m_isActive) { // +0x48: bool m_isActive
        m_currentState = newState; // +0x6C: void* m_currentState
        return;
    }
    destroyState(m_currentState);   // FUN_00957060 – clean up old state
    initializeState(newState);      // FUN_009574f0 – set up new state
    debugLog("UpdateMainMenu", 0, someGlobalData, 1, someOtherData); // FUN_005a04a0
}