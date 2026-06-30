// FUNC_NAME: TNLConnection::writeGhostPacket
// Address: 0x004a5ce0
// Constructs a sorted ghost packet for transmission: collects active ghosts, applies optional filter, sorts by priority, and stores into packet buffer.

void TNLConnection::writeGhostPacket(uint* thisPtr, uint* filterTable)
{
    uint* ghost;
    int i, j;
    int* objList;
    uint ghostId;
    uint subIdx;
    ushort* filterEntry;
    uint* objPtr;
    int priority;
    bool found;
    uint bitMaskLo, bitMaskHi;
    uint64 bitMask;

    // Constants for stack arrays (replaced with static allocations)
    // Note: Original code uses alloca_probe for large stack arrays; we keep as fixed-size but compressed.
    // In practice these would be dynamic but Ghidra decompiler shows them on stack.
    // We'll use local arrays for clarity, sizes based on max counts.
    const int MAX_GHOSTS = 750;
    int sortedPriorities[MAX_GHOSTS];
    uint ghostFlags[MAX_GHOSTS*2]; // pairs of uint
    int* ghostPtrs[MAX_GHOSTS];
    ushort* filterPtrs[MAX_GHOSTS];
    int activeCount = 0;
    int packetGhostCount = 0;
    int collectedGhosts[MAX_GHOSTS]; // stack array for collected ghost pointers

    // Read ghost manager pointer and item count
    uint* mgr = *(uint**) (thisPtr + 0x10); // pointer to ghost manager or scope list
    uint totalItems = *(ushort*)(mgr + 0x5a); // +0x5a: number of ghost groups
    ghostId = 0;

    // DAT_0122342c is global ghost manager singleton (or network manager base)
    int* ghostMgrBase = (int*)0x0122342c;
    int* ghostMgrTable = (int*)(*ghostMgrBase + 0x38); // offset 0x38 might be vtable? Actually base+0x38 used.

    while (ghostId < totalItems)
    {
        // Each ghost group is at mgr[0x38] + ghostId * 0x30
        ghost = *(uint**)(*(int*)(mgr + 0x38) + ghostId * 0x30);
        if (ghost == 0) continue;

        // Check if ghost is valid via some callback (FUN_00443880 looks up something)
        int tableIdx = FUN_00443880(&ghost);
        if (tableIdx < 0) continue;

        // Access a vtable entry (8 bytes per entry, offset 4 for function pointer)
        int* vtableEntry = (int*)(*(int*)(ghostMgrBase + 0x2c) + 4 + tableIdx * 8);
        if (vtableEntry == 0) continue;

        // Call a function on the ghost? Returns a pointer (maybe a ghost container)
        int* ghostContainer = (int*)(*(code*)*vtableEntry)(ghost, thisPtr);
        if (ghostContainer == 0) continue;

        // Now iterate sub-items inside this ghost group (e.g., individual ghost objects)
        subIdx = 0;
        ushort numSubItems = *(ushort*)(ghost + 0xb); // +0x0b: number of sub-ghosts
        if (numSubItems == 0) continue;

        do {
            uint* subGhost = *(uint**)(ghost[0x9] + subIdx * 4); // +0x09: array of pointers
            filterEntry = 0;

            // Optional filter: if filterTable provided, look for matching (ghostId, subIdx) pair
            if (filterTable != 0)
            {
                uint filterCount = *filterTable;
                ushort* filterList = (ushort*)(filterTable[1]);
                for (i = 0; i < filterCount; i++)
                {
                    if (filterList[i*4] == ghostId && filterList[i*4+1] == subIdx)
                    {
                        filterEntry = &filterList[i*4];
                        break;
                    }
                }
            }

            // Check if this sub-ghost is already in our sorted list
            found = false;
            int existingIdx = 0;
            for (i = 0; i < activeCount; i++)
            {
                if ((uint*)ghostPtrs[i] == subGhost && filterPtrs[i] == filterEntry)
                {
                    existingIdx = i;
                    found = true;
                    break;
                }
            }

            if (found)
            {
                // Already present; just set a flag bit
                bitMask = (uint64)1 << existingIdx;
                ghostFlags[existingIdx*2] |= (uint)bitMask;
                ghostFlags[existingIdx*2+1] |= (uint)(bitMask >> 32);
                goto nextSubGhost;
            }

            // New ghost: add to active list if space
            if (activeCount < MAX_GHOSTS - 1)
            {
                // Some global stats for debugging? (DAT_01205478)
                // Original code tracked a global counter and stored an ID from filterEntry+2.
                // Not needed for logic, but note it.
                // We can ignore or comment:
                // DAT_01205478 = DAT_01205478 + 1;
                // *(int*)(&DAT_01163fec + DAT_01205478 * 4) = (filterEntry ? *(filterEntry+2) : 0);

                // Compute priority using ghost manager function at base+0x44 / base+0x54
                priority = 0;
                int* prioFuncTable = (int*)(ghostMgrBase + 0x44); // offset 0x44: number of functions?
                int numPrioFuncs = *(int*)(ghostMgrBase + 0x44);
                if (numPrioFuncs > 0)
                {
                    // Binary search on subGhost ID (uint) using a sorted table at base+0x40
                    int* sortedTable = *(int**)(ghostMgrBase + 0x40);
                    int low = 0, high = numPrioFuncs - 1;
                    int mid;
                    uint target = *subGhost;
                    while (low <= high)
                    {
                        mid = (low + high) / 2;
                        if (sortedTable[mid*2] < target)
                            low = mid + 1;
                        else if (sortedTable[mid*2] > target)
                            high = mid - 1;
                        else
                            break;
                    }
                    if (mid < numPrioFuncs && sortedTable[mid*2] == target)
                    {
                        int* entry = &sortedTable[mid*2];
                        code* priorityFunc = (code*)entry[1]; // +4 offset to function
                        if (priorityFunc != 0)
                            priority = priorityFunc(subGhost, thisPtr);
                    }
                    else
                    {
                        // Fallback: use base+0x54 if available
                        code* fallback = *(code**)(ghostMgrBase + 0x54);
                        if (fallback)
                            priority = fallback(subGhost, thisPtr);
                    }
                }

                // Add to active lists
                sortedPriorities[activeCount] = priority;
                ghostFlags[activeCount*2] = 0;
                ghostFlags[activeCount*2+1] = 0;
                ghostPtrs[activeCount] = (int*)subGhost;
                filterPtrs[activeCount] = filterEntry;
                activeCount++;

                existingIdx = activeCount - 1; // index of newly added
                // Set the flag for this ghost
                bitMask = (uint64)1 << existingIdx;
                ghostFlags[existingIdx*2] |= (uint)bitMask;
                ghostFlags[existingIdx*2+1] |= (uint)(bitMask >> 32);
            }
nextSubGhost:
            subIdx++;
        } while (subIdx < numSubItems);

        // After processing all sub-ghosts, call a method on the container to check if it needs to be sent?
        // Original: call (*(code**)(*ghostContainer + 0x70))(); and if non-zero, set a bit in thisPtr+0x50/0x54.
        // This is likely marking this ghost group as "dirty" for packet inclusion.
        // We'll replicate:
        int containerVtable = *ghostContainer;
        bool isDirty = (*(code**)(containerVtable + 0x70))();
        if (isDirty)
        {
            uint64 mask = (uint64)1 << packetGhostCount;
            *(uint*)(thisPtr + 0x50) |= (uint)mask;
            *(uint*)(thisPtr + 0x54) |= (uint)(mask >> 32);
        }

        // Store collected ghost container pointer into local array for later copy
        collectedGhosts[packetGhostCount] = (int)ghostContainer;
        packetGhostCount++;
        ghostId++;
    }

    // After iterating all groups, copy the collected ghost containers to thisPtr's array at +0x5c/+0x60
    if (packetGhostCount > 0)
    {
        FUN_004a7b00(packetGhostCount); // probably reserve memory
        int currentCapacity = *(int*)(thisPtr + 0x60); // +0x60: count/size
        int newSize = packetGhostCount;
        if (currentCapacity == *(int*)(thisPtr + 100)) // some capacity field? Actually +0x64? Let's assume +0x64 placeholder
        {
            // Double capacity if necessary
            if (currentCapacity == 0)
                newSize = 1;
            else
                newSize = currentCapacity * 2;
            FUN_004a7b00(newSize);
        }
        int* destArray = *(int**)(thisPtr + 0x5c); // +0x5c: pointer to array
        int destCount = *(int*)(thisPtr + 0x60);
        for (i = 0; i < packetGhostCount; i++)
        {
            if (destArray != 0)
                destArray[destCount] = collectedGhosts[i];
            *(int*)(thisPtr + 0x60) = destCount + 1;
            destCount++;
        }
    }

    // Now sort the active ghosts by priority and write them to another array at +0x68/+0x6c
    if (activeCount > 0)
    {
        FUN_004a7bf0(activeCount); // resize array
        int* sortedArrayBase = *(int**)(thisPtr + 0x68); // +0x68: base of sorted array (16-byte entries)
        int sortedCount = 0;
        int* priorityArray = sortedPriorities;
        uint* flagsArray = ghostFlags;
        for (i = 0; i < activeCount; i++)
        {
            // For each ghost, get its priority (might differ from computed? actually we already have)
            // Original calls a vtable method at ghostPtrs[i][0] + 0x74 to get a key (uint16)
            int* ghostObj = (int*)ghostPtrs[i];
            uint16 objKey = (*(uint16(**)(void))(*(int*)ghostObj + 0x74))(); // from vtable
            // Insert into sorted list at thisPtr+0x68 (binary search)
            int insertPos = sortedCount - 1;
            int j;
            for (j = sortedCount - 1; j >= 0; j--)
            {
                ushort* entry = (ushort*)(sortedArrayBase + 4 + j * 16); // each entry: [0] ptr, [2] key, [4] flagsLo, [6] flagsHi? Actually structure: 0:ptr, 2:key (ushort), 4:flagsLo, 6:flagsHi
                uint existingKey = (uint)entry[0]; // not exactly; the structure is 16 bytes: int* (4 bytes), uint16 (2 bytes), padding? Looking at original: they write *puVar9 = piVar3 (ptr), *(ushort*)(puVar9+1)=objKey, puVar9[2]=flagsLo, puVar9[3]=flagsHi
                // So layout: offset +0: ptr, +4: key (ushort), +6: padding? Actually they write *(undefined2 *)(puVar9+1) which is byte offset 4 (since puVar9 is uint*), so key at +4 of the 16-byte block.
                // Let's model:
                // struct SortedEntry { int* ptr; uint16 key; uint16 pad; uint flagsLo; uint flagsHi; };
                SortedEntry* entry = (SortedEntry*)(sortedArrayBase + j * 16);
                if (entry->key <= objKey)
                    break;
                insertPos = j - 1;
            }
            // Now check capacity and insert
            if (sortedCount < *(int*)(thisPtr + 0x6c)) // +0x6c: current count
            {
                // shift entries down
                for (int k = sortedCount; k > insertPos + 1; k--)
                {
                    memcpy(&sortedArrayBase[k*16], &sortedArrayBase[(k-1)*16], 16);
                }
                // write new entry
                SortedEntry* newEntry = (SortedEntry*)(sortedArrayBase + (insertPos+1)*16);
                newEntry->ptr = ghostObj;
                newEntry->key = objKey;
                newEntry->flagsLo = flagsArray[i*2];
                newEntry->flagsHi = flagsArray[i*2+1];
                sortedCount++;
            }
        }
        // Update count
        *(int*)(thisPtr + 0x6c) = sortedCount;
        // Clear unused entries? Original code zeros them after loop.
        for (i = 0; i < activeCount; i++)
        {
            SortedEntry* entry = (SortedEntry*)(sortedArrayBase + i * 16);
            entry->key = 0;
            entry->ptr = 0;
            entry->flagsLo = 0;
            entry->flagsHi = 0;
        }
    }

    return;
}