// FUNC_NAME: MultiplayerScenarioManager::showWaitingForHost
void MultiplayerScenarioManager::showWaitingForHost(void)
{
    undefined4 *localArray; // stack-allocated array for message parameters
    undefined4 local_110;
    undefined4 local_c;
    undefined4 local_8;
    undefined4 local_4;

    // Check if the multiplayer manager and its host connection are active
    if ((DAT_01223484 != 0) && (*(int *)(DAT_01223484 + 0xc) != 0)) {
        local_c = 0;
        local_8 = 0;
        local_4 = 0;
        localArray = &PTR_LAB_00d79770; // Pointer to a static table of function pointers / action IDs
        local_110 = 5; // Number of elements in the table
        FUN_008a2f80(&localArray); // Call to process the action table (likely UI callback setup)
        FUN_0096f7a0("$mp_waiting_for_host", 1); // Show localized string with priority/flag 1
        FUN_008b5d40(); // Start a timer or transition to waiting state
    }
    return;
}