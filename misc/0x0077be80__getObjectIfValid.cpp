// FUNC_NAME: getObjectIfValid
// Address: 0x0077be80
// Role: Returns a value (likely a pointer) from a global manager if the input parameter is non-zero.

// Returns a value from a global manager (DAT_0112afe8) if param_1 is non-zero, otherwise returns 0.
// param_1 likely represents a handle or index that must be non-zero to be valid.
int __stdcall getObjectIfValid(int param_1)
{
    if (param_1 != 0) {
        // Retrieve value from global table/manager at DAT_0112afe8
        return FUN_0043b870(*(int*)0x0112afe8);
    }
    return 0;
}