// FUNC_NAME: SimManager::isIdFree
// Function address: 0x00650370
// Identified role: Check if a given ID is free (not present) in the hash table stored at this+0x11c.
// The hash table uses separate chaining with bucket nodes:
//   Node (bucket): +0x18 = pointer to first entry in linked list
//                  +0x10 = pointer to next bucket
//   Entry:         +0x0c = pointer to next entry
//                  +0x08 = stored ID (int)

bool __thiscall SimManager::isIdFree(int id)
{
    int* pBucket = *(int**)(this + 0x11c);  // first bucket node

    if (pBucket == nullptr)
        return true;  // empty table => ID is free

    do {
        // search the current bucket's linked list of entries
        for (int* pEntry = *(int**)(pBucket + 0x18); pEntry != nullptr; pEntry = *(int**)(pEntry + 0x0c))
        {
            if (*(int*)(pEntry + 0x08) == id)
                return false;  // ID found in table => not free
        }
        pBucket = *(int**)(pBucket + 0x10);  // advance to next bucket
        if (pBucket == nullptr)
            return true;  // no more buckets, ID not found => free
    } while (true);
}