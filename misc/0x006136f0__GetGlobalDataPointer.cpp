// FUNC_NAME: GetGlobalDataPointer
// Returns a pointer to a global singleton data structure at 0x011f69f0.
// This is likely a static getter for a manager or core system object.
void* GetGlobalDataPointer(void)
{
    // Address of global singleton instance
    return &DAT_011f69f0;
}