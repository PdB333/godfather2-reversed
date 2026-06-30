// FUNC_NAME: getGlobalManagerIfEnabled
int FUN_00726870(int param_1)
{
    // param_1 likely indicates whether the global manager is requested.
    // If non-zero, return the result of the inner getter on DAT_01131040.
    // Otherwise return 0 (null).
    if (param_1) {
        return FUN_0043b870(DAT_01131040);
    }
    return 0;
}