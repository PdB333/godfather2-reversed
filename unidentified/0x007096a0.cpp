// FUN_007096a0: EntityHandleManager::allocateHandle
void __thiscall EntityHandleManager::allocateHandle(int thisPtr)
{
    int typeField;
    int handle;
    int vtableBase;
    int vtablePtr;
    int idResult;

    // Likely a global initialization or lock
    someBeginFunction();

    // Check conditions: typeField at +0x1bc should be nonzero and not equal to 0x48,
    // and handle field at -0x40 should be zero (i.e., not yet allocated)
    if ( (*(int*)(thisPtr + 0x1bc) != 0) &&
         (*(int*)(thisPtr + 0x1bc) != 0x48) &&
         (*(int*)(thisPtr - 0x40) == 0) )
    {
        // Derive vtable base from typeField
        if (*(int*)(thisPtr + 0x1bc) == 0) {
            vtableBase = 0;
        } else {
            vtableBase = *(int*)(thisPtr + 0x1bc) - 0x48; // Subtract size of something?
        }

        // Call a virtual function at offset 0x58+4 to get some ID or reference
        // The call returns something (likely an ID) stored in local_8
        vtablePtr = *(int*)(vtableBase + 0x58);
        (*(code**)(vtablePtr + 4))(local_8);

        // Allocate and initialize a handle ID
        handle = allocateHandleStorage(&stack0xffffffec, 4); // stack0xffffffec likely address of local_8
        writeHandleData(handle, &local_8, 4);  // Copy the ID into handle
        writeHandleData(handle, &s_nextHandleCounter, 4); // Copy global counter? (DAT_0112ab40)
        *(int*)(thisPtr - 0x40) = handle;  // Store handle in object

        s_nextHandleCounter++;  // Increment global counter
    }
    return;
}