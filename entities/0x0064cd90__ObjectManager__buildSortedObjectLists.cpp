// FUNC_NAME: ObjectManager::buildSortedObjectLists
void ObjectManager::buildSortedObjectLists(void)
{
    // Global flags and lists
    static bool g_sortedListsBuilt = false; // at 0x0120588a
    int* pObjectListHead = (int*)0x012059ec; // linked list head of objects
    
    // Arrays for sorted lists per (bit, type) combination
    // Size: 4 bits * 3 types = 12 entries
    static int g_listSizes[12] = {};      // at 0x01223158
    static int g_listCapacities[12] = {}; // at 0x0122315c
    static int** g_listData[12] = {};     // at 0x01223160
    
    // Lookup tables for each bit (4 tables, each at offset 0x10 + bit*4)
    // These are used to store index of object in the sorted list
    static int* g_flagLookupTables[4] = { (int*)0x10, (int*)0x14, (int*)0x18, (int*)0x1c };
    
    // Per-list power-of-two size (exponent) used for hashing? at 0x012059f0
    static int g_listPow2[12] = {};
    
    if (g_sortedListsBuilt) return;
    
    int totalCollected = 0;
    int collectedCount = 0;
    
    for (int bit = 0; bit < 4; bit++) // iterate bits 0-3
    {
        int listBaseIndex = bit * 3; // each bit has 3 sub-lists (type 0,1,2)
        int lookupTableBase = (int)(g_flagLookupTables[bit]); // e.g. 0x10,0x14,...
        
        for (int type = 0; type < 3; type++)
        {
            int currentListIndex = listBaseIndex + type;
            
            // Collect all objects matching this type and having the bit set
            int* collected = nullptr;
            int numCollected = 0;
            
            for (int* pObj = pObjectListHead; pObj != nullptr; pObj = (int*)pObj[0x70/4]) // +0x70 next
            {
                if ((pObj[0xc/4] == type) && (pObj[0x4/4] & (1 << bit)))
                {
                    // Add to collected array
                    collected = (int*)realloc(collected, (numCollected + 1) * sizeof(int));
                    collected[numCollected] = (int)pObj;
                    numCollected++;
                }
            }
            
            if (numCollected > 0)
            {
                // Sort the collected objects by some key (comparator at 0x0064cd40)
                qsort(collected, numCollected, sizeof(int), &objectComparator);
                
                // Ensure capacity in the global sorted list for this (bit,type)
                int requiredCapacity = numCollected;
                if (g_listCapacities[currentListIndex] < requiredCapacity)
                {
                    int newCapacity = (requiredCapacity + 0x0f) & ~0x0f; // round to next multiple of 16
                    int* newData = (int*)malloc(newCapacity * sizeof(int));
                    
                    int oldSize = g_listSizes[currentListIndex];
                    if (oldSize > 0)
                    {
                        int* oldData = g_listData[currentListIndex];
                        for (int i = 0; i < oldSize; i++)
                            newData[i] = oldData[i];
                        free(oldData);
                    }
                    g_listCapacities[currentListIndex] = newCapacity;
                    g_listData[currentListIndex] = newData;
                }
                
                // Copy collected objects into global list
                for (int i = 0; i < numCollected; i++)
                {
                    g_listData[currentListIndex][i] = collected[i];
                }
                g_listSizes[currentListIndex] = numCollected;
                
                // Fill the lookup table for this bit: for each object, store its index
                // The lookup table is an array at address lookupTableBase, presumably large enough
                for (int i = 0; i < numCollected; i++)
                {
                    int objAddr = collected[i];
                    *(int*)(lookupTableBase + objAddr) = i; // store index at offset objAddr from lookupTableBase
                }
                
                // Compute power-of-two size (next power of two's exponent) for this list
                int nextPow2 = numCollected + 1;
                // Round up to next power of two
                if ((nextPow2 & (numCollected)) != 0) // if not already power of two
                {
                    float fNextPow2 = (float)nextPow2;
                    if (nextPow2 < 0)
                        fNextPow2 += 0.5f; // DAT_00e44578 likely 0.5f for rounding
                    int exponent = ((unsigned int)fNextPow2 >> 23) - 127 + 1; // bit shift hack to get exponent
                    nextPow2 = 1 << exponent;
                }
                else
                {
                    nextPow2 = numCollected + 1; // already power of two? Actually this is odd
                }
                // Compute exponent for storage
                float fNextPow2 = (float)nextPow2;
                if (nextPow2 < 0)
                    fNextPow2 += 0.5f;
                g_listPow2[currentListIndex] = ((unsigned int)fNextPow2 >> 23) - 127;
                
                // Free temporary collected array
                free(collected);
            }
        }
    }
    
    g_sortedListsBuilt = true;
    free(nullptr); // likely cleanup macro
}