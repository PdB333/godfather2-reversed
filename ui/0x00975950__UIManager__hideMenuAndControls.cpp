// FUNC_NAME: UIManager::hideMenuAndControls
void __fastcall UIManager::hideMenuAndControls(int thisPtr)
{
    // Clear input or timer
    FUN_0068c590(0);
    // Likely dereference a global state pointer
    FUN_004086d0(&DAT_0112ffd4);
    // Check if some condition is met (e.g., game is in a state to hide)
    char condition = FUN_00974ed0();
    if (condition) {
        *(uint8_t *)(thisPtr + 0x80) = 1; // +0x80: flag indicating menu hidden
    }
    // Set up a timer/callback with a small offset (0x14 from thisPtr)
    int offsetPtr = (thisPtr != 0) ? (thisPtr + 0x14) : 0;
    FUN_005c0d50(offsetPtr, &LAB_00975930, 0);
    // Game-specific UI commands
    FUN_005a04a0("HideMenu", 0, &DAT_00d8f7f8, 0);
    FUN_005a04a0("HideControls", 0, &DAT_00d8f7f8, 0);
}