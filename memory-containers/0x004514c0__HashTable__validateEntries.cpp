// FUNC_NAME: HashTable::validateEntries
// Function address: 0x004514c0
// Role: Validates integrity of hash table entries, checking for duplicates or corrupted entries
// Uses sentinel values to identify empty/deleted entries, computes polynomial hash, and verifies no collisions

void __thiscall HashTable::validateEntries(HashEntry *entries, int unusedFlag, uint32_t count)
{
    // Acquire lock at offset 0x6c8
    LockMutex((CRITICAL_SECTION *)((char *)this + 0x6c8));

    // Sentinel values for deleted entries
    const uint32_t DELETED0 = 0xbadbadba;
    const uint32_t DELETED1 = 0xbeefbeef;
    const uint32_t DELETED2 = 0xeac15a55;
    const uint32_t DELETED3 = 0x91100911;

    for (uint32_t i = 0; i < count; i++)
    {
        HashEntry &entry = entries[i];
        uint32_t f0 = entry.field0;
        uint32_t f1 = entry.field1;
        uint32_t f2 = entry.field2;
        uint32_t f3 = entry.field3;

        // Skip empty entries (all zeros) and deleted entries (sentinel pattern)
        bool isEmpty = (f0 == 0 && f1 == 0 && f2 == 0 && f3 == 0);
        bool isDeleted = (f0 == DELETED0 && f1 == DELETED1 &&
                          f2 == DELETED2 && f3 == DELETED3);

        if (!isEmpty && !isDeleted)
        {
            // Polynomial hash: ((((f0*33 + f1)*33 + f2)*33 + f3)
            uint64_t hash = (uint64_t)f0;
            hash = hash * 33 + f1;
            hash = hash * 33 + f2;
            hash = hash * 33 + f3;

            // Look up hash in main table; second parameter is likely flags/reserved
            void *slot = HashTableLookup((uint32_t)hash, 0);

            if (slot != nullptr)
            {
                // Dereference to get the object pointer stored at slot[0]
                void *obj = *(void **)slot;
                // Check if object exists and its second dword (offset +4) is non-zero
                if (obj && *(int *)((char *)obj + 4) != 0)
                {
                    // Duplicate or corrupted entry – trigger error handler
                    ReportHashCollision();
                }
            }
        }
    }

    // Release lock
    UnlockMutex();
}