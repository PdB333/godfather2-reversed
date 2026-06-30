// FUNC_NAME: FilterManager::setFilterByIndex

void __thiscall FilterManager::setFilterByIndex(uint index)
{
    // +0x20: pointer to DataManager or similar manager
    int *dataManager = *(int **)(this + 0x20);
    
    // +0xa4 in dataManager: maximum valid index
    // +0x3c in this: current filter index (stored as char* but actually uint)
    if (index >= *(uint *)(dataManager + 0xa4) || index == *(uint *)(this + 0x3c))
    {
        return;
    }
    
    // Store the new index
    *(uint *)(this + 0x3c) = index;
    
    // Derive a filter string from the index
    char *filterString;
    if (index < *(uint *)(dataManager + 0xa4))
    {
        // +0xac in dataManager: base of array of structures, each 0x61 bytes
        filterString = (char *)(index * 0x61 + *(int *)(dataManager + 0xac));
    }
    else
    {
        // Fallback empty string (global)
        filterString = &DAT_01222260;
    }
    
    // First loop: notify listeners with type > 1
    // +0x34: number of listeners
    // +0x30: pointer to array of listener pointers
    if (*(int *)(this + 0x34) != 0)
    {
        uint listenerCount = *(uint *)(this + 0x34);
        for (uint i = 0; i < listenerCount; i++)
        {
            int *listener = *(int **)(*(int *)(this + 0x30) + i * 4);
            // Listener structure: +4 points to sub-structure, +0x14 is type field
            if (*(uint *)(*(int *)(listener + 4) + 0x14) > 1)
            {
                FUN_00605c70(index, filterString); // Notify listener
            }
        }
    }
    
    // Second loop: iterate over filter entries and clear non‑matching ones
    // +0x28: number of entries
    // +0x24: pointer to array of entry pointers
    uint entryCount = *(uint *)(this + 0x28);
    if (entryCount != 0)
    {
        for (uint i = 0; i < entryCount; i++)
        {
            int *entry = *(int **)(*(int *)(this + 0x24) + i * 4);
            
            // Determine if the entry matches the filter string
            int cmpResult;
            if (filterString == nullptr || *filterString == '\0')
            {
                cmpResult = -1; // Empty filter: no match
            }
            else
            {
                // +0x24 in entry: stored string pointer
                char *entryString = *(char **)(entry + 0x24);
                if (entryString == nullptr)
                {
                    cmpResult = 1; // No string: no match
                }
                else
                {
                    cmpResult = __stricmp(entryString, filterString);
                }
            }
            
            if (cmpResult != 0)
            {
                // Entry does not match; remove its stored data
                // +0x34 in entry: hash ID for global hash table
                uint hashId = *(uint *)(entry + 0x34);
                if (hashId != 0)
                {
                    // Global hash table manager at DAT_0122337c
                    // +0x50: hash table array pointer
                    // +0x54: hash table size (number of slots)
                    int hashManager = *(int *)(DAT_0122337c + 0x50);
                    int hashSize   = *(int *)(DAT_0122337c + 0x54);
                    uint slot = hashId % hashSize;
                    uint *node = *(uint **)(hashManager + slot * 4);
                    while (node != nullptr)
                    {
                        if (*node == hashId)
                        {
                            if (node[1] != 0)
                            {
                                FUN_004048c0(node[1], 0); // Free/detach attached data
                            }
                            break;
                        }
                        node = (uint *)node[2];
                    }
                }
                // Clear entry fields
                *(uint *)(entry + 0x34) = 0; // hash ID
                *(uint *)(entry + 0x28) = 0; // flag (previously used for comparison?)
                if (*(char **)(entry + 0x24) != nullptr)
                {
                    // Zero out the first character of the stored string
                    **(char ***)(entry + 0x24) = 0;
                }
                FUN_006059c0(filterString); // Notify that filter changed
            }
        }
    }
    
    // Zero out multiple 16‑byte buffers (offsets 0x54, 0x64, 0x74, 0x84, 0x94, 0xa4, 0xb4, 0xc4, 0xd4, 0xe4)
    *(char *)(this + 0x54) = 0;
    *(char *)(this + 0x64) = 0; // 100 decimal
    *(char *)(this + 0x74) = 0;
    *(char *)(this + 0x84) = 0;
    *(char *)(this + 0x94) = 0;
    *(char *)(this + 0xa4) = 0;
    *(char *)(this + 0xb4) = 0;
    *(char *)(this + 0xc4) = 0;
    *(char *)(this + 0xd4) = 0;
    *(char *)(this + 0xe4) = 0;
    
    // Clear bits 1,2,3 in flags at +0x4c
    *(uint *)(this + 0x4c) &= ~0x2;
    *(uint *)(this + 0x4c) &= ~0x4;
    *(uint *)(this + 0x4c) &= ~0x8;
    
    // Initialize a local structure from a global and call init function
    int initData[3];
    initData[0] = DAT_01222240;
    initData[1] = 0;
    initData[2] = 0;
    FUN_00408a00(initData, 0);
}