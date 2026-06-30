// FUNC_NAME: resolveComponentData

struct HashNode {
    uint32_t key;       // +0x00
    void* value;        // +0x04
    HashNode* next;     // +0x08
};

struct HashTable {
    HashNode** buckets; // +0x04
    uint32_t numBuckets; // +0x08
};

struct GlobalHashData {
    // ... 
    HashTable* table;   // +0x08
};

// Assumes DAT_01223398 points to a GlobalHashData structure
// param1: destination key (another object ID)
// param2: source key (object ID to copy from)
// Copies 64 bytes from source data offset 0x30 to destination data offset 0x90
uint32_t* resolveComponentData(uint32_t sourceKey, uint32_t destKey) {
    GlobalHashData* globalData = *(GlobalHashData**)0x01223398;
    HashTable* table = globalData->table; // +8

    // Lookup sourceKey
    uint32_t bucketIndex = sourceKey % table->numBuckets;
    HashNode* node = table->buckets[bucketIndex];
    void* sourceValue = nullptr;

    while (node) {
        if (node->key == sourceKey) {
            sourceValue = node->value;
            break;
        }
        node = node->next;
    }

    if (!sourceValue) {
        sourceValue = nullptr;
    }

    // Lookup destKey
    bucketIndex = destKey % table->numBuckets;
    HashNode* destNode = table->buckets[bucketIndex];
    while (destNode) {
        if (destNode->key == destKey) {
            break;
        }
        destNode = destNode->next;
    }

    if (destNode && destNode->value) {
        uint32_t* destData = (uint32_t*)destNode->value;
        uint32_t* destOffset = (uint32_t*)(destData[0x24]); // offset 0x90 from value

        if (destOffset && sourceValue) {
            uint8_t* src = (uint8_t*)sourceValue + 0x30;
            uint8_t* dst = (uint8_t*)destOffset;
            // Copy 16 dwords (64 bytes)
            for (int i = 0; i < 16; i++) {
                dst[i*4] = src[i*4];
            }
        }
    }

    // Return value from division (unclear purpose)
    uint32_t* result = (uint32_t*)(destKey / table->numBuckets);
    return result;
}