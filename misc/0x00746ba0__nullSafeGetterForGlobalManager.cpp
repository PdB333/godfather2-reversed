// FUNC_NAME: nullSafeGetterForGlobalManager
// Function address: 0x00746ba0
// This function checks if the 'this' pointer (param_1) is non-null,
// and if so, calls a subroutine (FUN_0043b870) with a global handle (DAT_01131064)
// and returns its result. Otherwise returns 0.
// The parameter is likely a 'this' pointer from a __thiscall convention.
int __thiscall nullSafeGetterForGlobalManager(void* this_ptr) {
    // DAT_01131064 is a global pointer/handle (likely to a manager or singleton)
    if (this_ptr != nullptr) {
        // FUN_0043b870 probably retrieves a resource or state from the global
        return FUN_0043b870(DAT_01131064);
    }
    return 0;
}