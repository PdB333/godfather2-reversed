// FUNC_NAME: SomeManager::rebuildLinkedLists

// Rebuilds three linked lists of hash nodes from stored string/ID components.
// Called during initialization or when internal state changes.
void __fastcall SomeManager::rebuildLinkedLists(int thisPtr) {
    undefined4 local_50 = 0;
    undefined4 local_4c = 0;
    undefined4 local_48 = 0;
    undefined1 local_44[4]; // small buffer for hash input
    undefined4* local_40 = 0; // linked list traversal pointer
    int local_3c[9]; // unused? initially zero

    // Build a hash input from global constants (likely a base path + offset)
    FUN_008c9650(thisPtr, &local_50, _DAT_00e544b0, _DAT_00e544ac, 0);

    // First list: build from globals (e.g., a hardcoded identifier)
    undefined4 local_c = DAT_00e446f4;
    undefined4 local_8 = DAT_00d5d934;
    undefined4 local_4 = 3;
    int newHash = FUN_008ca3b0(local_44); // convert buffer to hash

    int* headPtr = (int*)(thisPtr + 0x7e4); // pointer to head of first list
    if (*headPtr != newHash) {
        if (*headPtr != 0) {
            FUN_004daf90(headPtr); // delete old head node
        }
        *headPtr = newHash;
        if (newHash != 0) {
            // Link new node: set its 'next' to the previous second node (or null)
            *(int*)(thisPtr + 0x7e8) = *(int*)(newHash + 4);
            *(int**)(newHash + 4) = headPtr; // update double-linked backward pointer
        }
    }

    // Second list: from member variables at +0x7bc, +0x7b8, +0x7c0, +0x7c4
    undefined4 local_18 = *(int*)(thisPtr + 0x7bc);
    undefined4 local_14 = *(int*)(thisPtr + 0x7b8);
    undefined4 local_c = *(int*)(thisPtr + 0x7c0);
    undefined4 local_8 = *(int*)(thisPtr + 0x7c4);
    undefined4 local_4 = 0;
    newHash = FUN_008ca3b0(local_44);

    headPtr = (int*)(thisPtr + 0x804);
    if (*headPtr != newHash) {
        if (*headPtr != 0) {
            FUN_004daf90(headPtr);
        }
        *headPtr = newHash;
        if (newHash != 0) {
            *(int*)(thisPtr + 0x808) = *(int*)(newHash + 4);
            *(int**)(newHash + 4) = headPtr;
        }
    }

    // Third list: from member variables at +0x7cc, +0x7c8, +2000 (0x7d0), +0x7d4
    local_18 = *(int*)(thisPtr + 0x7cc);
    local_14 = *(int*)(thisPtr + 0x7c8);
    local_c = *(int*)(thisPtr + 0x7d0); // offset 2000 = 0x7d0
    local_8 = *(int*)(thisPtr + 0x7d4);
    local_4 = 0;
    newHash = FUN_008ca3b0(local_44);

    headPtr = (int*)(thisPtr + 0x7fc);
    if (*headPtr != newHash) {
        if (*headPtr != 0) {
            FUN_004daf90(headPtr);
        }
        *headPtr = newHash;
        if (newHash != 0) {
            *(int*)(thisPtr + 0x800) = *(int*)(newHash + 4);
            *(int**)(newHash + 4) = headPtr;
        }
    }

    // Clean up the temporary linked list held in local_3c (appears unused)
    if (local_3c[0] != 0) {
        FUN_004daf90(local_3c);
    }

    // Clean up any nodes still in the traversal pointer (never used)
    while (local_40 != 0) {
        undefined4* next = (undefined4*)local_40[1];
        local_40[1] = 0;
        local_40[0] = 0;
        local_40 = next;
    }
}