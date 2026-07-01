// FUNC_NAME: GodfatherGameManager::setMenuActive

bool __thiscall GodfatherGameManager::setMenuActive(char enable)
{
    // locals for a 12-byte structure passed to engine function
    int someId;
    int zero1;
    byte zero2;

    if (enable != '\0') {
        // Check if game is in appropriate state for menu activation
        // g_apManagers[3] likely points to UIManager or MenuManager
        if ((g_apManagers[3] == 0) &&
            ((g_pNetSession == 0 ||
              (*(int *)(g_pNetSession + 0x28) == 0 && *(int *)(g_pNetSession + 0x2c) == 0)) ||
             (g_pNetSession == (void *)-0x28))) &&
            (*(int *)(g_pInputDeviceManager + 8) != 0)) {
            // Allow menu: disable flag and play opening sound/dialog
            this->m_bIsMenuActive = 0;
            (**(code **)(*g_apManagers + 0x14))(&LAB_0094fbf0,0,0xc1683e52);
        }
        else {
            // Block menu: set flag to 1
            this->m_bIsMenuActive = 1;
        }
    }
    if (this->m_bIsMenuActive != '\0') {
        // Clear bit 5 in some global flag (likely pause/inventory state)
        *(uint *)(g_pGameStateManager + 0x6c) = *(uint *)(g_pGameStateManager + 0x6c) & 0xffffffdf;
        // Reset a timer or ID
        someId = g_someTimerID;
        zero1 = 0;
        zero2 = 0;
        FUN_00408a00(&someId,0);
        // Unpause or resume something
        FUN_0040eaf0(1);
        return 1;
    }
    return 0;
}