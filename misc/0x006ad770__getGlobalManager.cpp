// FUNC_NAME: getGlobalManager
int __cdecl getGlobalManager(int bCreateIfNeeded)
{
    // Returns a pointer to a global manager or 0 if bCreateIfNeeded is false.
    // If true, acquires/creates the manager via internal function.
    if (bCreateIfNeeded != 0)
    {
        return FUN_0043b870(DAT_0112afb8); // internal getter, global singleton pointer
    }
    return 0;
}