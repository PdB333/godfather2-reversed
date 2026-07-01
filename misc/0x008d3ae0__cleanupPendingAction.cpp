// FUNC_NAME: cleanupPendingAction
// Address: 0x008d3ae0
// Role: Cleans up a pending action or resource associated with the object, likely removing it from a global manager.
void __thiscall cleanupPendingAction(void* thisPtr)
{
    // Check if a flag at offset +0x80 indicates a pending action/resource
    if (*(char*)((int)thisPtr + 0x80) != '\0')
    {
        // Call the global cleanup/unregister function on the manager (DAT_0112f9dc)
        someCleanupFunction(&g_someManager); // FUN_004086d0
        // Clear the flag
        *(char*)((int)thisPtr + 0x80) = '\0';
    }
}