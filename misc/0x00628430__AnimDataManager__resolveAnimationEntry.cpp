// FUNC_NAME: AnimDataManager::resolveAnimationEntry
// Address: 0x00628430
// This function resolves an animation entry from a hash table (or linked list) and writes it to a stack-like data buffer.
// It appears to handle two cases: when some count is < 2, it searches a hash table; otherwise it uses a different path.
// The function manipulates a write pointer at this+0x08 and reads/writes structures at this+0x10 and other offsets.

void __thiscall AnimDataManager::resolveAnimationEntry(void)
{
    int *pEntry; // Generic pointer for entry traversal
    int *pNewEntry; // Another temp
    int iCount; // Some count from the manager
    undefined4 uVal4; // Temporary for function returns

    // Fetch manager pointer from this+0x10, then dereference to get something at +0x30
    int iManager = *(int *)(*(int *)((int)this + 0x10) + 0x30);

    // Check if some count at iManager+0x1c is less than 2
    if (*(int *)(iManager + 0x1c) < 2) {
        // Hash table lookup: use a global random-like value modulo (2^(iManager[7] & 31) - 1 | 1) to get an entry offset
        int iHashIndex = (DAT_00e445ac % ((1 << (*(char *)(iManager + 7) & 0x1f)) - 1U | 1));
        pEntry = (int *)(*(int *)(iManager + 0x10) + iHashIndex * 0x14);
        do {
            // Look for an entry where *pEntry == 3 and the float at pEntry[1] equals DAT_00e2b04c
            if ((*pEntry == 3) && ((float)pEntry[1] == DAT_00e2b04c)) {
                pEntry = pEntry + 2; // Move past the two ints
                goto LAB_006284b8;
            }
            pEntry = (int *)pEntry[4]; // Follow linked list (next pointer at offset 4)
        } while (pEntry != (int *)0x0);
        // If not found, use a default static data
        pEntry = &DAT_00e2a93c;
    } else {
        // If count >= 2, use a different path: fetch from iManager+0x0c + 8
        pEntry = (int *)(*(int *)(iManager + 0xc) + 8);
    }

LAB_006284b8:
    // Write the found entry data to the write stack buffer
    int *pWritePtr = *(int **)((int)this + 8); // Current write pointer
    *pWritePtr = *pEntry;
    pWritePtr[1] = pEntry[1];
    // Advance write pointer by 8 bytes (two ints)
    *(int *)((int)this + 8) = (int)this + 8 + 8; // Actually: *(int *)((int)this + 8) += 8;

    // Now check the newly written data? It actually goes back by 8 and inspects.
    pNewEntry = (int *)(*(int *)((int)this + 8) - 8);
    if (pNewEntry == (int *)0x0) {
        return;
    }
    if (*pNewEntry != 0) {
        return; // If first int is non-zero, exit
    }

    // If first int is zero, we modify the write pointer (pop?).
    *(int **)((int)this + 8) = pNewEntry; // Revert write pointer by 8?

    // Check some counts at this+0x10 -> +0x20 and +0x24
    if (*(uint *)(*(int *)((int)this + 0x10) + 0x20) <= *(uint *)(*(int *)((int)this + 0x10) + 0x24)) {
        FUN_00627360(); // Trigger some overflow handling?
    }

    // Write a new entry with type 5 and a value from FUN_00637c50
    undefined4 *puVar5 = *(undefined4 **)((int)this + 8);
    *puVar5 = 5;
    uVal4 = FUN_00637c50(0,0);
    puVar5[1] = uVal4;
    *(int *)((int)this + 8) = *(int *)((int)this + 8) + 8;

    // Duplicate the previous entry (the one we just popped?) by copying the last two ints
    puVar5 = *(undefined4 **)((int)this + 8);
    *puVar5 = puVar5[-2];
    puVar5[1] = puVar5[-1];
    *(int *)((int)this + 8) = *(int *)((int)this + 8) + 8;

    // Now modify something based on the type of the earlier entry (at -0x10 and -0x8)
    int iVar1 = *(int *)((int)this + 8);
    pNewEntry = (int *)(iVar1 - 8);
    if (*pNewEntry == 0) {
        pNewEntry = (int *)(*(int *)((int)this + 0x10) + 0x34); // Use default
    }
    if (*(int *)(iVar1 - 0x10) == 5) {
        *(int *)(*(int *)(iVar1 - 0xc) + 8) = pNewEntry[1]; // Set some field at +8 of the object pointed by the entry's second int
    } else if (*(int *)(iVar1 - 0x10) == 7) {
        *(int *)(*(int *)(iVar1 - 0xc) + 8) = pNewEntry[1];
    }
    *(int *)((int)this + 8) = *(int *)((int)this + 8) - 8; // Pop the last pair

    // Again check overflow
    if (*(uint *)(*(int *)((int)this + 0x10) + 0x20) <= *(uint *)(*(int *)((int)this + 0x10) + 0x24)) {
        FUN_00627360();
    }

    // Write two entries of type 4 with values from FUN_00638920
    puVar5 = *(undefined4 **)((int)this + 8);
    *puVar5 = 4;
    uVal4 = FUN_00638920();
    puVar5[1] = uVal4;
    *(int *)((int)this + 8) = *(int *)((int)this + 8) + 8;

    if (*(uint *)(*(int *)((int)this + 0x10) + 0x20) <= *(uint *)(*(int *)((int)this + 0x10) + 0x24)) {
        FUN_00627360();
    }

    puVar5 = *(undefined4 **)((int)this + 8);
    *puVar5 = 4;
    uVal4 = FUN_00638920();
    puVar5[1] = uVal4;
    *(int *)((int)this + 8) = *(int *)((int)this + 8) + 8;

    // Call FUN_00638020 and copy the result (which seems to be a pointer to new entry) and then pop two pairs
    iVar1 = *(int *)((int)this + 8);
    puVar5 = (undefined4 *)FUN_00638020();
    *puVar5 = *(undefined4 *)(iVar1 - 8);
    puVar5[1] = *(undefined4 *)(iVar1 - 4);
    *(int *)((int)this + 8) = *(int *)((int)this + 8) - 0x10; // Pop 16 bytes (two entries)

    puVar5 = *(undefined4 **)((int)this + 8);
    *puVar5 = puVar5[-2];
    puVar5[1] = puVar5[-1];
    *(int *)((int)this + 8) = *(int *)((int)this + 8) + 8; // Push a duplicate of the previous one again? Actually it's a move?

    // Now update the original hash table: look up again and store back
    int iManager2 = *(int *)(*(int *)((int)this + 0x10) + 0x30);
    int iWritePos = *(int *)((int)this + 8);
    if (*(int *)(iManager2 + 0x1c) < 2) {
        // Hash table lookup again, same pattern
        int iHashIndex2 = (DAT_00e445ac % ((1 << (*(char *)(iManager2 + 7) & 0x1f)) - 1U | 1));
        pEntry = (int *)(*(int *)(iManager2 + 0x10) + iHashIndex2 * 0x14);
        do {
            if ((*pEntry == 3) && ((float)pEntry[1] == DAT_00e2b04c)) {
                goto LAB_0062866f;
            }
            pEntry = (int *)pEntry[4];
        } while (pEntry != (int *)0x0);
    } else {
        pEntry = *(int **)(iManager2 + 0xc);
LAB_0062866f:
        pEntry = pEntry + 2;
        if (pEntry != &DAT_00e2a93c) {
            goto LAB_00628693;
        }
    }
    pEntry = (int *)FUN_00637d60();

LAB_00628693:
    // Write back the data from the top of the stack to the found entry
    *pEntry = *(int *)(iWritePos - 8);
    pEntry[1] = *(int *)(iWritePos - 4);
    *(int *)((int)this + 8) = *(int *)((int)this + 8) - 8; // Pop the last pair
    return;
}