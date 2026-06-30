// FUNC_NAME: SomeManager::flushDirtyFlags
// Address: 0x006a42c0
// Role: Checks if any of the first 4 integer fields of the object are non-zero (dirty flags), and if so, calls a setup function (likely debug/profile) then a processing function that copies state into a temporary buffer.
// Note: The assignment to local_10 appears to be an artifact of a jump table or inline assembly; it is not used in the decompiled flow.

void __thiscall SomeManager::flushDirtyFlags(int *thisPtr)
{
    char buffer[16]; // 16-byte temporary buffer (e.g., for a transformation result)
    char *labelPtr;   // decompiler artifact: address of a label (LAB_006a4210)

    // Check if any of the first four fields are non-zero (dirty flags)
    if (thisPtr[0] != 0 || thisPtr[1] != 0 || thisPtr[2] != 0 || thisPtr[3] != 0)
    {
        // Call setup/initialization function (e.g., debug enter marker, mutex lock, or pipeline flush)
        FUN_005e3070();

        // Assign label pointer (likely used for a jump table or as a return address; not used in this reconstructed flow)
        labelPtr = (char *)0x006a4210;

        // Call processing function that transforms or copies data from thisPtr into buffer (e.g., encode, compress, or apply pending changes)
        FUN_005e6500(thisPtr, buffer);
    }
    // If no flags are dirty, do nothing
}