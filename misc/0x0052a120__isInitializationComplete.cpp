//FUNC_NAME: isInitializationComplete
// Function address: 0x0052a120
// Role: Checks if the game initialization is complete by comparing global state variables.
// Returns 1 if initialization is done, 0 otherwise.

int isInitializationComplete(void)
{
    // Global state variables (likely timers or flags)
    // DAT_01125240: current initialization state
    // DAT_00e2b05c: target initialization state
    // DAT_00e2af44: elapsed time or progress counter
    // DAT_0112523c: threshold time or required progress
    if ((g_currentInitState != g_targetInitState) && (g_elapsedProgress <= g_requiredProgress)) {
        return 1;
    }
    return 0;
}