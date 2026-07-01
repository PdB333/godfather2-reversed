// FUNC_NAME: Entity::cleanupAttachments
void __fastcall Entity::cleanupAttachments(int thisPtr)
{
    // +0x58: pointer to some manager/state data (e.g., entity info table)
    int* managerData = *(int**)(thisPtr + 0x58);
    int managerIndex = (int)managerData;  // used as index into global array DAT_00002494

    // Check flag at managerData+0x184 bit 1 (0x2)
    if ((*(uint*)(managerData + 0x184) >> 1) & 1)
    {
        // If flag set, perform some global operation (e.g., disable sound system)
        FUN_00460880();
    }

    // +0x9c: some handle/ID (0 = invalid, 0x48 = special sentinel)
    int handle1 = *(int*)(thisPtr + 0x9c);
    // +0x88: pointer to a vtable-based object
    int* objPtr = *(int**)(thisPtr + 0x88);

    // Only release if handle1 is valid (non-zero and not sentinel 0x48)
    if (handle1 != 0 && handle1 != 0x48 && objPtr != 0)
    {
        // Call virtual function at offset 8 (likely Release/DecRef)
        (**(code**)(*objPtr + 8))();
    }

    // +0x94: another managed object pointer
    int* childPtr = (int*)(thisPtr + 0x94);
    if (*childPtr != 0)
    {
        // Stop sound associated with this object (using manager index and object pointer)
        FUN_00424ee0(*(undefined4*)(&DAT_00002494 + managerIndex), *childPtr);

        // If the object is not null, call its virtual function with argument 1 (Release/Delete)
        if (*childPtr != 0)
        {
            (**(code**)*(*childPtr))(1);
        }

        // Deallocate memory for this object
        if (*childPtr != 0)
        {
            FUN_004daf90(childPtr);
            *childPtr = 0;
        }
    }

    // +0x8c: third managed object pointer (similar pattern)
    int* anotherPtr = (int*)(thisPtr + 0x8c);
    if (*anotherPtr != 0 && *anotherPtr != 0x48)
    {
        // Compute base pointer (subtract 0x48 to get actual object start)
        int base;
        if (*anotherPtr == 0)
            base = 0;
        else
            base = *anotherPtr - 0x48;

        // Read flag at base+0x54
        char flag = *(char*)(base + 0x54);

        // Recompute base for sound call (same logic)
        int soundBase;
        if (*anotherPtr == 0)
            soundBase = 0;
        else
            soundBase = *anotherPtr - 0x48;

        // Play a release sound (global sound ID DAT_00d5eee4, channel 6?)
        FUN_00424df0(*(undefined4*)(&DAT_00002494 + managerIndex), soundBase, DAT_00d5eee4, 6, 0, 0);

        if (flag == 0)
        {
            // Check if all four sub-flags at managerData offsets 0x2ba4-0x2bb0 are zero
            if (*(int*)(managerData + 0x2ba4) == 0 &&
                *(int*)(managerData + 0x2ba8) == 0 &&
                *(int*)(managerData + 0x2bac) == 0 &&
                *(int*)(managerData + 0x2bb0) == 0)
            {
                // If all zero, release the object anyway
                if (*anotherPtr != 0)
                {
                    int* obj = (int*)(*anotherPtr - 0x48);
                    if (obj != 0)
                        (**(code**)*obj)(1);  // call virtual Release
                }
            }
            else
            {
                // Otherwise, allocate 0x3c bytes? (maybe allocation for new object)
                if (*anotherPtr == 0)
                    FUN_004088c0(0x3c);
                else
                    FUN_004088c0(*anotherPtr - 0xc);  // something based on old pointer
            }
        }

        // Deallocate memory for this object
        if (*anotherPtr != 0)
        {
            FUN_004daf90(anotherPtr);
            *anotherPtr = 0;
        }

        // Signal that a cleanup is done (parameter 5)
        FUN_006915c0(5);
    }
}