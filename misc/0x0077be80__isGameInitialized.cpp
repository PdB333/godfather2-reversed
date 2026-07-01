// FUNC_NAME: isGameInitialized
// Address: 0x0077be80
// Role: Checks if the game is initialized, using a global state pointer.
// Returns non-zero if initialized (via FUN_0043b870), zero if param_1 is null.

int isGameInitialized(int param_1)
{
    // param_1 likely indicates a subsystem or context (e.g., player index or mode)
    if (param_1 != 0) {
        // DAT_0112afe8 is a global pointer to a game state/manager object
        // FUN_0043b870 likely returns an initialization flag or status
        return FUN_0043b870(DAT_0112afe8);
    }
    return 0;
}