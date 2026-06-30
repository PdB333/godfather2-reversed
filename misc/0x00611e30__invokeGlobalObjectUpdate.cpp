// FUNC_NAME: invokeGlobalObjectUpdate
void invokeGlobalObjectUpdate(void)
{
    // Global pointer to a singleton object (likely a manager class)
    // If non-null, call its virtual function at vtable offset 0x20 (5th virtual method)
    if (DAT_012058e8 != (int *)0x0) {
        // WARNING: Could not recover jumptable at 0x00611e3f. Too many branches
        // WARNING: Treating indirect jump as call
        (**(code **)(*DAT_012058e8 + 0x20))();
    }
}