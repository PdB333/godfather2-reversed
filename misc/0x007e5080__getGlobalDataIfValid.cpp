// FUNC_NAME: getGlobalDataIfValid
// Address: 0x007e5080
// Role: Returns a value from a global pointer if the input parameter is non-zero, otherwise returns 0.
// This appears to be a simple validation check before accessing a global resource.

int getGlobalDataIfValid(int param_1)
{
    if (param_1 != 0) {
        // Call to retrieve data from global pointer (DAT_0112afb8)
        return FUN_0043b870(DAT_0112afb8);
    }
    return 0;
}