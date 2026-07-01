// FUNC_NAME: EntityManager::findFirstEntity
// Address: 0x0088dbb0
// This function iterates over a collection of entities (up to 255) managed by the object at `this`.
// It calls a predicate callback (FUN_00889ee0) with a pointer to a search data structure.
// Returns the first non-zero result from the predicate (e.g., an entity pointer or ID), or 0 if none matches.

int __fastcall EntityManager::findFirstEntity(void* thisPtr, void* searchData)
{
    uint8_t index = 0;                                                  // Byte loop counter
    uint32_t count = *(uint32_t*)((uint8_t*)thisPtr + 0x148);           // +0x148: number of entities in the manager

    if (count != 0)
    {
        do
        {
            // Call the predicate with the search data; returns non-zero when a match is found
            int result = FUN_00889ee0(searchData);                      // searchData is passed as a pointer to the predicate
            if (result != 0)
            {
                return result;
            }
            ++index;
        } while ((uint32_t)index < count);                              // Loop up to count (max 255 due to byte index)
    }

    return 0;                                                           // No matching entity found
}