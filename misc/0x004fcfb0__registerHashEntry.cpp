// FUNC_NAME: registerHashEntry

void registerHashEntry(uint32_t key, uint32_t param2, uint32_t param3, uint32_t param4, uint32_t param5, uint32_t param6)
{
    // Allocation info: { flags?, size?, padding? }
    uint32_t allocInfo[4];
    allocInfo[1] = 2;          // allocation flags
    allocInfo[2] = 0x10;       // allocation size hint (actual size 0x28)
    allocInfo[3] = 0;          // padding

    // Allocate 40-byte hash entry object
    uint32_t* newEntry = (uint32_t*)allocateMemory(0x28, &allocInfo[1]); // FUN_009c8ed0

    uint32_t globalValue = g_someGlobal; // DAT_00e2b1a4

    if (newEntry != nullptr)
    {
        // Set vtable pointer at offset 0x00
        newEntry[0] = (uint32_t)&HASH_ENTRY_VTABLE; // PTR_FUN_00e37ae0

        // Initialize fields (offsets relative to entry start)
        newEntry[1] = param2;   // +0x04
        newEntry[2] = param4;   // +0x08
        newEntry[3] = param5;   // +0x0C
        newEntry[4] = param3;   // +0x10
        newEntry[5] = param6;   // +0x14
        newEntry[6] = globalValue; // +0x18
        newEntry[7] = 0;        // +0x1C
        newEntry[8] = 0;        // +0x20
        newEntry[9] = 0;        // +0x24
    }

    // Store key in allocation info for hash table insertion
    allocInfo[0] = key;

    // Compute hash bucket index
    uint32_t hashTableSize = *(uint32_t*)(*(int*)(g_pHashTableManager + 8) + 8); // dereference chain
    uint32_t bucketIndex = key % hashTableSize;

    // Use local pointer for insertion (by address)
    uint32_t* entryPointer = newEntry;
    hashTableInsert(allocInfo, &entryPointer, bucketIndex); // FUN_00423cf0
}