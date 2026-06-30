// FUNC_NAME: getOptionalGlobalObject
// Address: 0x006bc8b0
// Returns a global singleton pointer only if the given flag is non-zero.
// The flag acts as an enable/disable gate for the global object.
// Internally calls the global accessor FUN_0043b870 with DAT_01131040 (likely a pointer to the singleton instance).
// Return 0 if flag is 0, otherwise returns result from the global accessor.

int getOptionalGlobalObject(int enabled)
{
    if (enabled != 0) {
        // Access global singleton via static pointer (DAT_01131040).
        // FUN_0043b870 likely casts or dereferences it to return the actual object pointer.
        int result = FUN_0043b870(DAT_01131040);
        return result;
    }
    return 0;
}