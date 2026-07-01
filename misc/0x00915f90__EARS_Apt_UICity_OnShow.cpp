// Xbox PDB: EARS_Apt_UICity_OnShow
// FUNC_NAME: GodfatherGameManager::updateObjectiveDisplay
// Address: 0x00915f90
// Role: Updates the current mission objective display and sets the appropriate input/mode state based on whether objectives are active.

void __thiscall GodfatherGameManager::updateObjectiveDisplay(void)
{
    // 32-byte buffer for objective text formatting
    char objectiveTextBuf[32];

    // Initial update call (likely syncs internal objective state)
    FUN_00957df0();

    // Check if there is a current objective (pointer at game manager +0x28)
    if (*(int*)(DAT_01129938 + 0x28) != 0) {
        // Format objective text: buffer, max length, format string, objective pointer
        // PTR_LAB_00d78708 is likely a format specifier (e.g., "%s")
        FUN_005c4630(objectiveTextBuf, 0x20, (char*)&PTR_LAB_00d78708, *(int*)(DAT_01129938 + 0x28));
        // Call UI scripting to show the objective (function name, arg0, target string, arg1, formatted text)
        FUN_005a04a0("ShowCurrentObjective", 0, (char*)&DAT_00d850c8, 1, objectiveTextBuf);
    }

    // Check if any active objectives exist (counter at another global +0x78)
    if (0 < *(int*)(DAT_01130020 + 0x78)) {
        // Objectives active: set mode 0 (normal input) and update after
        FUN_0097b630(0, 1);
        FUN_00957350();
        return;
    }

    // No active objectives: set mode 1 (perhaps free roam/disabled input) and update
    FUN_0097b630(1, 1);
    FUN_00957350();
    return;
}