// Xbox PDB: EARS_Apt_UIOnlineMenu_PopHistory
// FUNC_NAME: ScreenStateManager::applyHistoryState
void __fastcall ScreenStateManager::applyHistoryState(int this)
{
    // Check if the current state is either "Normal" (1) or "Transition" (2)
    // Presumably state at offset +0xdc (our internal state tracking)
    if ((*(int *)(this + 0xdc) != 1) && (*(int *)(this + 0xdc) != 2)) {
        // If not in normal or transition state, pop history (go back to previous screen)
        FUN_005a04a0("PopHistory", 0, &DAT_00d8cdec, 0);
        FUN_00965720(); // Apply the popped history state
        return;
    }
    // If in normal or transition state, clear the history (no previous screen to go back to)
    FUN_005a04a0("ClearHistory", 0, &DAT_00d8cdec, 0);
    FUN_00965720(); // Apply the cleared history state
    return;
}