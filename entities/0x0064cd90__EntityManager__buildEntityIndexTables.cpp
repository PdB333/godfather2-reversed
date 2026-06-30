// FUNC_NAME: EntityManager::buildEntityIndexTables
void EntityManager::buildEntityIndexTables(void)
{
    // Global flag to ensure one-time initialization
    if (g_bInitialized) return;

    // Global linked list of entities
    EntityNode* pNode = g_pEntityListHead;

    // Temporary storage for collecting pointers of a specific category and bit
    EntityNode** collectedList = nullptr;
    size_t collectedCount = 0;
    size_t collectedCapacity = 0;

    // Base offset for storing index in entity (0x10, 0x14, 0x18, 0x1c)
    uint baseOffset = 0x10;
    int tableRowOffset = 0; // increments by 3 each outer loop
    byte bitIndex = 0; // which bit in flags field to test

    // Outer loop: iterate over 4 bits (bit 0..3)
    while (baseOffset < 0x20)
    {
        // Inner loop: iterate over 3 categories (0,1,2)
        for (uint category = 0; category < 3; ++category)
        {
            collectedCount = 0;
            collectedCapacity = 0;

            // Traverse linked list to collect entities matching current category and bit
            pNode = g_pEntityListHead;
            while (pNode != nullptr)
            {
                // Check if entity belongs to this category and has the required bit set
                if (pNode->category == category &&
                    (pNode->flags & (1 << bitIndex)) != 0)
                {
                    // Ensure collection array has capacity
                    growCollectionArray(&collectedList, &collectedCapacity, collectedCount + 1);
                    collectedList[collectedCount] = pNode;
                    collectedCount++;
                }
                pNode = pNode->next; // next pointer at offset 0x70
            }

            if (collectedCount > 0)
            {
                // Sort the collected pointers using comparator at 0x0064cd40
                qsort(collectedList, collectedCount, sizeof(EntityNode*), entityComparator);

                // Compute index into global category tables: tableRow = bit*3 + category
                int tableIndex = tableRowOffset + category;

                // Ensure capacity of the global table array
                if (g_categoryTables[tableIndex].capacity < collectedCount)
                {
                    // Reallocate to next power of 2 (or at least +16)
                    int newCapacity = (collectedCount & ~0xF) + 0x10;
                    EntityNode** newList = (EntityNode**)malloc(newCapacity * sizeof(EntityNode*));
                    if (g_categoryTables[tableIndex].count > 0)
                    {
                        memcpy(newList, g_categoryTables[tableIndex].pList, 
                               g_categoryTables[tableIndex].count * sizeof(EntityNode*));
                    }
                    free(g_categoryTables[tableIndex].pList);
                    g_categoryTables[tableIndex].pList = newList;
                    g_categoryTables[tableIndex].capacity = newCapacity;
                }

                // Copy sorted pointers into global table
                for (uint i = 0; i < collectedCount; ++i)
                {
                    g_categoryTables[tableIndex].pList[i] = collectedList[i];
                }
                g_categoryTables[tableIndex].count = collectedCount;

                // Write index (position in sorted list) into each entity's structure
                for (uint i = 0; i < collectedCount; ++i)
                {
                    // Store index at offset baseOffset (0x10,0x14,0x18,0x1c) in the entity
                    *(int*)((uintptr_t)collectedList[i] + baseOffset) = i;
                }

                // Compute power-of-two size for the table (unused? stored in another global)
                uint nextPower2 = collectedCount + 1;
                if ((nextPower2 & collectedCount) != 0)
                {
                    float f = (float)nextPower2;
                    // Bit hack to get next power of 2
                    nextPower2 = 1 << ((int)((*(uint32_t*)&f >> 23) - 0x7f));
                }
                // Store the power-of-two exponent (probably for hash table)
                // g_categoryTablePower[tableIndex] = (int)(log2(nextPower2));
                // The code stores to &DAT_012059f0 + tableIndex*4
                // We'll keep it as an array of 12 ints
                g_categoryTablePower[tableIndex] = (int)(nextPower2 >> 23) - 0x7f;

                // Free temporary collection (if any)
                if (collectedList != nullptr)
                {
                    free(collectedList);
                    collectedList = nullptr;
                }
                collectedCount = 0;
                collectedCapacity = 0;
            }
        }

        // Move to next bit: offset increments by 4, table row by 3, bit index by 1
        tableRowOffset += 3;
        baseOffset += 4;
        bitIndex++;
    }

    // Mark initialization complete
    g_bInitialized = true;

    // Free any leftover temporary collection (should be null)
    if (collectedList != nullptr)
        free(collectedList);
}

// Helper function to grow the collection array (call to FUN_0064d260)
void EntityManager::growCollectionArray(EntityNode*** pList, size_t* pCapacity, size_t required)
{
    if (required > *pCapacity)
    {
        size_t newCapacity = (*pCapacity == 0) ? 16 : (*pCapacity + 16);
        // Actually the original code uses a function to allocate, but we can inline
        EntityNode** newList = (EntityNode**)malloc(newCapacity * sizeof(EntityNode*));
        if (*pList != nullptr)
        {
            memcpy(newList, *pList, (*pCapacity) * sizeof(EntityNode*));
            free(*pList);
        }
        *pList = newList;
        *pCapacity = newCapacity;
    }
}

// Comparator function (address 0x0064cd40) - assumed to compare by some key
int __cdecl EntityManager::entityComparator(const void* a, const void* b)
{
    // Compare two EntityNode* by some field (e.g., ID)
    const EntityNode* nodeA = *(const EntityNode**)a;
    const EntityNode* nodeB = *(const EntityNode**)b;
    // Assume comparison by some uint32 key at offset 0x0? Or by pointer?
    // We'll just return a placeholder
    return (nodeA < nodeB) ? -1 : (nodeA > nodeB);
}