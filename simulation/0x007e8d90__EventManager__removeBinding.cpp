//FUNC_NAME: EventManager::removeBinding
void __thiscall EventManager::removeBinding(void* thisPtr, void* pObject, uint32_t eventType)
{
    // pObject is expected to be non-null
    if (pObject == nullptr) {
        return;
    }

    // Get the name string from the object (offset +0x6c)
    const char* nameStr = *(const char**)((uint8_t*)pObject + 0x6c);
    if (nameStr == nullptr) {
        nameStr = &DAT_0120546e; // Default empty string
    }

    // Compute hash using the object's name and an additional ID (offset +0x70)
    uint32_t hash = FUN_004db3a0(eventType, nameStr, *(uint32_t*)((uint8_t*)pObject + 0x70));

    // Global hash table: gHashTable is a pointer to an array of bucket heads
    // gHashTable[0] = base pointer, gHashTable[1] = number of buckets
    extern uint32_t* gHashTable; // Actually a struct with base and count
    uint32_t bucketIndex = hash % gHashTable[1];
    uint32_t* bucketHead = *(uint32_t**)(gHashTable[0] + bucketIndex * 4);

    // Walk the linked list in the bucket to find the entry with matching hash
    while (bucketHead != nullptr) {
        if (*bucketHead == hash) {
            // Found the entry; bucketHead[1] is the index into the local array
            uint32_t entryIndex = bucketHead[1];
            // Clear the two fields at this+0x354 + entryIndex*8 and this+0x358 + entryIndex*8
            *(uint32_t*)((uint8_t*)thisPtr + 0x354 + entryIndex * 8) = 0;
            *(uint32_t*)((uint8_t*)thisPtr + 0x358 + entryIndex * 8) = 0;
            return;
        }
        bucketHead = (uint32_t*)bucketHead[2]; // next pointer
    }
    // If not found, do nothing
}