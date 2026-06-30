// FUNC_NAME: ObjectManager::getObjectFromHandle
// Function at 0x00726890: Retrieves an object from a global table if handle is non-zero
// param_1: handle (e.g., entity ID or pointer)
// Returns: object pointer or value from global DAT_01131070, or 0 if handle is 0
undefined4 __cdecl objectManagerGetObjectFromHandle(int handle)
{
    if (handle != 0) {
        // Call global manager function with global singleton
        return FUN_0043b870(*(void **)0x01131070);
    }
    return 0;
}