// FUNC_NAME: getGlobalManagerIfAllowed
int getGlobalManagerIfAllowed(int param_1) // returns a pointer (int is used as pointer), param_1 acts as a flag
{
    if (param_1 != 0) {
        // DAT_01130950 is a global pointer, likely to some manager instance (e.g., AudioDataManager, SimManager)
        return (int)FUN_0043b870(*DAT_01130950); // calls a function to retrieve the instance; assuming DAT_01130950 stores pointer to singleton
    }
    return 0; // return null if condition fails
}