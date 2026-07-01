//FUNC_NAME: UIManager::enterTab
void __fastcall UIManager::enterTab(int this)
{
    // Log entering a tab
    debugPrint("EnterTab", 0, &DAT_00d88708, 0);
    // Call some initialization or transition function
    FUN_00956b30();
    
    // Check current tab state (offset +0x5c)
    if (*(int *)(this + 0x5c) == 4) {
        // Handle tab 4
        FUN_0092b440();
        return;
    }
    if (*(int *)(this + 0x5c) == 5) {
        // Handle tab 5
        FUN_0092c1d0();
        return;
    }
    // Default handling for other tabs
    FUN_00957350();
    return;
}