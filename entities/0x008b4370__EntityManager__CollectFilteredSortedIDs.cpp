// FUNC_NAME: EntityManager::CollectFilteredSortedIDs
int* __thiscall EntityManager::CollectFilteredSortedIDs(int this, int* outArray)
{
    int iVar2;
    int iVar3;
    int current;
    undefined4* puVar1;

    // Initialize output array (pointer, size, capacity = 0)
    outArray[0] = 0;       // data pointer
    outArray[1] = 0;       // count
    outArray[2] = 0;       // capacity

    // Get head of linked list of entities (offset 0x60 from this)
    current = *(int*)(this + 0x60);
    if (current != 0) {
        // If head's next pointer is null, treat as empty list
        if (*(int*)(current + 8) == 0) {
            current = 0;
        }
        while (current != 0) {
            // Get current entity pointer via global iterator function
            iVar2 = (*(code*)PTR_FUN_00e35c28)();
            // Check bit 1 of entity flags at offset 0x30
            if ((*(uint*)(iVar2 + 0x30) >> 1 & 1) != 0) {
                // Get second pointer (possibly the ID or sub-object)
                iVar3 = (*(code*)PTR_FUN_00e35c28)();
                // Grow dynamic array if needed (resize factor 2)
                if (outArray[1] == outArray[2]) {
                    if (outArray[2] == 0) {
                        iVar2 = 1;
                    } else {
                        iVar2 = outArray[2] * 2;
                    }
                    // Reallocate (FUN_00486800 likely a realloc wrapper)
                    FUN_00486800(iVar2);
                }
                // Append ID at offset +8 of second pointer
                puVar1 = (undefined4*)(outArray[0] + outArray[1] * 4);
                outArray[1] = outArray[1] + 1;
                if (puVar1 != (undefined4*)0x0) {
                    *puVar1 = *(undefined4*)(iVar3 + 8);
                }
            }
            // Advance to next entity
            (*_UNK_00e35c2c)();
        }
        // Sort collected IDs if more than one
        if (1 < (uint)outArray[1]) {
            qsort((void*)outArray[0], outArray[1], 4, (_PtFuncCompare*)&LAB_008aab50);
        }
    }
    return outArray;
}