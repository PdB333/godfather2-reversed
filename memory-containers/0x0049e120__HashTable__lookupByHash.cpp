// FUNC_NAME: HashTable::lookupByHash
// 0x0049e120: Hash table lookup - finds a value by 13-bit hash key
// Global hash table at DAT_012054ac: array of 0x2000 (8192) pointers to bucket heads
// Struct BucketNode (size 0x14): 
//   +0x0: (unknown, likely flags or padding)
//   +0x8: value (returned)
//   +0xc: full hash key (uint32)
//   +0x10: next pointer

struct BucketNode {
    uint32_t unknown; // +0x0
    int32_t  value;   // +0x8
    uint32_t hashKey; // +0xc
    BucketNode* next; // +0x10
};

// Global hash table base pointer (needs linking)
extern BucketNode* g_hashTable[0x2000]; // DAT_012054ac

int32_t HashTable::lookupByHash(uint32_t param_1) {
    if (param_1 == 0) {
        return 0;
    }

    // Mask to 13-bit index (0x1fff = 8191)
    uint32_t index = param_1 & 0x1fff;
    BucketNode* bucket = g_hashTable[index];
    if (bucket == nullptr) {
        return 0;
    }

    // Traverse linked list to find matching full hash
    while (bucket->hashKey != param_1) {
        bucket = bucket->next;
        if (bucket == nullptr) {
            return 0;
        }
    }

    // Found match, return stored value (or 0 if node somehow null)
    if (bucket != nullptr) {
        return bucket->value;
    }
    return 0;
}