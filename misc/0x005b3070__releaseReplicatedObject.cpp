// FUNC_NAME: releaseReplicatedObject
// Address: 0x005b3070
// Role: Releases a replicated network object if it is the currently active object in the manager.
//       Checks validity via a flag at bit 15 of the object's first word, then verifies
//       that the object is the current one in the manager before removing it.

void __fastcall releaseReplicatedObject(uint32 unused, uint32 sessionId, uint* objectPtr)
{
    uint flags[4];          // Local variable for flags/output from the registration call

    // Call the underlying registration/validation function.
    // Likely parameters: object's internal ID, sessionId, 0, output buffer, and pointer to object pointer (may be modified).
    FUN_005b1f80(*objectPtr, sessionId, 0, flags, &objectPtr);

    uint* originalPtr = objectPtr;  // Save possibly modified pointer

    // Check object is non-null and has the valid flag (bit 15) set
    if (objectPtr != nullptr && ((*objectPtr >> 15) & 1) == 1)
    {
        // Check if object's field at offset 0x54 (index 0x15) is non-zero
        if (objectPtr[0x15] != 0)
        {
            uint managerHandle = FUN_005bc1e0();  // Get the replication manager handle

            // Check if object's field at offset 0x34 (index 0xd) is non-zero
            if (objectPtr[0xd] != 0)
            {
                uint* activeObject = FUN_005bb150(managerHandle);  // Get current active object from manager
                if (activeObject == originalPtr)
                {
                    FUN_005bad80(managerHandle);  // Remove the active object from manager
                }
            }
        }
        FUN_005aa310();  // Perform final update (e.g., network flush)
    }
}