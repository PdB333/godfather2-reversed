// FUNC_NAME: SetGlobalFlag
// Address: 0x00413940
// Sets a global byte flag (DAT_0120524b) to the given value.
// This is likely a simple state flag (e.g., pause, menu open, input lock).
void SetGlobalFlag(char flagValue)
{
    // Global byte DAT_0120524b - probably a game state flag
    g_globalFlag = flagValue;
}