// FUNC_NAME: ScriptSystem::releaseScript

int __thiscall ScriptSystem::releaseScript(int thisPtr) {
    int scriptDataPtr;
    int *dataPtr;
    uint *dataPtr2;
    int index;
    float idFloat;
    uint idRounded;
    int poolEntryPtr;

    // Get the current data pointer from this+0x0c
    dataPtr = *(int **)(thisPtr + 0xc);
    // Check against capacity at this+0x08
    if (dataPtr >= *(int **)(thisPtr + 8)) {
        return 0;
    }
    if (dataPtr == (int *)0x0) {
        return 0;
    }

    // Type check: must be 3 or 4
    if (*dataPtr != 3) {
        if (*dataPtr != 4) {
            return 0;
        }
        // For type 4, additional validation via FUN_00636850
        if (FUN_00636850(&thisPtr) == 0) {
            return 0;
        }
    }

    // Re-read data pointer (may have been changed by validation?)
    dataPtr2 = *(uint **)(thisPtr + 0xc);
    if (dataPtr2 < *(uint **)(thisPtr + 8) && dataPtr2 != (uint *)0x0) {
        if (*dataPtr2 == 3) {
            idFloat = (float)dataPtr2[1];
        } else if (*dataPtr2 == 4) {
            // Validate again? (redundant check)
            if (FUN_00636850(&thisPtr) != 0) {
                idFloat = (float)dataPtr2[1];
            } else {
                idFloat = 0.0f;
            }
        } else {
            idFloat = 0.0f;
        }
    } else {
        idFloat = 0.0f;
    }

    // Round float to integer ID
    idRounded = (uint)(longlong)ROUND(idFloat);
    if (idRounded < 0x80) {
        // Global script pool base: DAT_0122346c + 0x14
        // Each pool entry is 0x54 (84) bytes
        poolEntryPtr = (int)(idRounded * 0x54 + 0x122346c + 0x14);
        // Ensure the pool entry points back to this script
        if (*(int *)poolEntryPtr == thisPtr) {
            // Decrement active scripts if the entry was not already freed
            if (*(char *)(poolEntryPtr + 0x4d) == '\0') {
                _DAT_01205404--;  // Global active script count
            }
            // Clear pool entry fields
            *(int *)poolEntryPtr = 0;          // +0x00: pointer to script?
            *(int *)(poolEntryPtr + 4) = 0;     // +0x04: ?
            *(int *)(poolEntryPtr + 8) = 0;     // +0x08: ?
            *(char *)(poolEntryPtr + 0x4c) = 0; // +0x4c (actually poolEntryPtr+0x13*4? The code uses piVar4+0x13 as byte, but piVar4 is int*, so (int*)(poolEntryPtr+0x4c)?) Re-check:
            // The decompile: *(undefined1 *)(piVar4 + 0x13) = 0; (since piVar4 is int*, offset in bytes is 0x4c). So +0x4c is cleared.
            // Also: *(undefined1 *)((int)piVar4 + 0x4d) = 1; // +0x4d set to 1 (freed flag)
            // *(undefined1 *)((int)piVar4 + 0x4e) = 0; // +0x4e cleared
            // *(undefined1 *)(piVar4 + 3) = 0; // +0x0c cleared (piVar4+3 as int* -> byte offset 0xc)
            // Fix offsets to match bytes precisely:
            *(char *)(poolEntryPtr + 0x4c) = 0;  // +0x4c
            *(char *)(poolEntryPtr + 0x4d) = 1;  // +0x4d: freed flag (1 = freed)
            *(char *)(poolEntryPtr + 0x4e) = 0;  // +0x4e
            *(char *)(poolEntryPtr + 0x0c) = 0;  // +0x0c: type? Actually piVar4+3 means byte at offset 0xc (since int* points to byte offset 0). So clear the type field of the pool entry?
        }
    }

    return 0;
}