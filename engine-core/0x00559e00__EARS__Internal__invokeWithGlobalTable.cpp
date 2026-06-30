// FUNC_NAME: EARS::Internal::invokeWithGlobalTable
void invokeWithGlobalTable(uint arg1, uint arg2, uint arg3, uint arg4)
{
    // Global table pointer at 0x00dcf974, likely a vtable or dispatch table
    void** tablePtr = &PTR_LAB_00dcf974;

    // Global value at 0x00e445dc (unused, possibly debug or legacy)
    uint unusedGlobal = DAT_00e445dc;

    // Call inner function with reordered parameters + table pointer
    // The inner function likely dispatches a method based on table entries
    FUN_00c09cc0(arg2, arg1, arg3, &tablePtr);
}