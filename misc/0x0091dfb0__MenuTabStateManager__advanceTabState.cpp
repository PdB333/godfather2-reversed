// FUNC_NAME: MenuTabStateManager::advanceTabState
void __fastcall MenuTabStateManager::advanceTabState(void* thisPtr) // +0xB8 = currentTabState (enum)
{
    int newState;
    int currentState = *(int*)((unsigned char*)thisPtr + 0xB8); // +0xB8 = current tab state
    switch (currentState)
    {
    case 0xD: // Tab "A"
        disableTab(&g_TabController, 0);
        newState = 0xE;
        break;
    case 0xE:
        disableTab(&g_TabController, 0);
        newState = 0xF;
        break;
    case 0xF:
        disableTab(&g_TabController, 0);
        newState = 0x10;
        break;
    case 0x10:
    case 0x11:
        disableTab(&g_TabController, 0);
        newState = 0xD; // return to start of sequence
        break;
    case 0x12:
        disableTab(&g_TabController, 0);
        newState = 0x13;
        break;
    case 0x13:
        disableTab(&g_TabController, 0);
        newState = 0x14;
        break;
    case 0x14:
        disableTab(&g_TabController, 0);
        newState = 0x15;
        break;
    case 0x15:
        disableTab(&g_TabController, 0);
        newState = 0x16;
        break;
    case 0x16:
        disableTab(&g_TabController, 0);
        newState = 0x17;
        break;
    case 0x17:
        disableTab(&g_TabController, 0);
        newState = 0x18;
        break;
    case 0x18:
        disableTab(&g_TabController, 0);
        newState = 0x12; // loop back to the 0x12 cycle
        break;
    default:
        return;
    }
    setTabState(newState); // updates internal state
    logDebug("SetSectionTabs", 0, &g_sectionTabName, 0); // debug logging
    updateTabUI(1, 0); // refresh tab UI
}