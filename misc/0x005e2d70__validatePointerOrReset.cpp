// FUNC_NAME: validatePointerOrReset
/**
 * Function at 0x005e2d70
 * Checks if the object pointed to by param_2 passes validation (via FUN_005e2490).
 * If invalid, sets *param_2 to nullptr and returns 0. Otherwise returns 1.
 * Likely a safety guard to ensure a pointer is valid before use.
 */
int __cdecl validatePointerOrReset(void* param_1, void** param_2)
{
    char isValid = FUN_005e2490(param_2); // Checks validity of the pointer
    if (isValid == '\0') {
        *param_2 = 0; // Reset to null on failure
        return 0;
    }
    return 1;
}