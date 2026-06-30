// FUNC_NAME: HashTableManager::lookupAndProcessEntry

struct HashTableEntry {
    uint32 key;           // +0x00
    uint32* pData;        // +0x04 - pointer to data (or data itself if small)
    HashTableEntry* pNext; // +0x08
};

struct HashTableHandle {
    HashTableEntry** buckets; // +0x04 - pointer to array of bucket pointers
    uint32* sizePtr;          // +0x08 - pointer to size value (number of buckets?)
    // Note: actual offsets may differ; adjusted for dereference pattern
};

uint32* HashTableManager::lookupAndProcessEntry(uint32 key, uint32* sourceData, uint32 extraParam) {
    HashTableHandle* handle = *(HashTableHandle**)gHashTableGlobal; // DAT_01223398
    uint32 bucketSize = *(uint32*)(handle->sizePtr); // uVar1 = table size
    uint32 bucketIndex = key / bucketSize; // local variable for bucket index (return if not found)
    HashTableEntry* entry = handle->buckets[key % bucketSize];

    if (entry != nullptr) {
        // Search linked list for matching key
        while (entry->key != key) {
            entry = entry->pNext;
            if (entry == nullptr) {
                return (uint32*)bucketIndex; // return bucket index if not found
            }
        }

        // If entry found and has data pointer
        if ((entry != nullptr) && (entry->pData != nullptr)) {
            uint32 localBuffer[16]; // 0x10 * 4 bytes
            // Copy 16 uint32 values from source to local buffer
            for (int i = 0; i < 16; ++i) {
                localBuffer[i] = sourceData[i];
            }
            // Process the copied data (pass extraParam to sub-function)
            return (uint32*)processEntryData(extraParam);
        }
    }

    return (uint32*)bucketIndex; // default return: bucket index
}