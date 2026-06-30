// FUNC_NAME: checkAndReturnGlobalData
// Address: 0x0074c710
// Role: Checks if a flag/pointer is non-zero, then returns value from a global manager.
// Calls: FUN_0043b870 (likely a getter on a global singleton at DAT_01131070)

int checkAndReturnGlobalData(int conditionFlag)
{
    if (conditionFlag != 0)
    {
        // Call a function on the global object referenced by DAT_01131070
        // DAT_01131070 is likely a pointer to a manager singleton (e.g., AudioDataManager, SimManager, etc.)
        return FUN_0043b870(DAT_01131070);
    }
    return 0;
}