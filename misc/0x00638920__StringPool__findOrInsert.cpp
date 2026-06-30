// FUNC_NAME: StringPool::findOrInsert
// Address: 0x00638920
// Role: Hash table lookup with insertion on miss. Computes a custom hash over the key bytes,
// then searches the bucket chain. If the key is found, returns; otherwise calls the insert helper.

struct StringPoolNode {
    StringPoolNode* next;       // +0x00
    uint32_t field_4;           // +0x04 (unknown)
    uint32_t field_8;           // +0x08 (unknown)
    uint32_t length;            // +0x0C
    uint8_t keyData[1];         // +0x10 (variable-length)
};

struct HashTableData {
    StringPoolNode** buckets;   // +0x00
    uint32_t field_4;           // +0x04
    uint32_t size;              // +0x08 (must be power of 2)
};

void __thiscall StringPool::findOrInsert(StringPool* this, uint8_t* key, uint32_t length) {
    // Compute a stepped reverse hash over the key bytes
    uint32_t step = (length >> 5) + 1;   // process roughly every 32nd byte
    uint32_t index = length;
    uint32_t hash = length;
    if (step <= length) {
        do {
            uint32_t prevIndex = index - 1;
            index -= step;
            hash ^= (uint32_t)key[prevIndex] + hash * 0x20 + (hash >> 2);
        } while (step <= index);
    }

    // Access the hash table data stored at offset 0x10 of 'this'
    HashTableData* table = *(HashTableData**)((uint8_t*)this + 0x10);
    uint32_t bucketIndex = (table->size - 1) & hash;
    StringPoolNode* node = table->buckets[bucketIndex];

    // Search the bucket chain
    while (node != nullptr) {
        if (node->length == length) {
            // Compare the actual key data starting at node->keyData (offset 0x10)
            uint8_t* nodeKey = (uint8_t*)(node + 4); // node + 4 words == offset 0x10
            uint32_t remaining = length;
            uint32_t* nodeWord = (uint32_t*)nodeKey;
            uint32_t* keyWord = (uint32_t*)key;
            while (remaining >= 4) {
                if (*nodeWord != *keyWord) goto keyMismatch;
                nodeWord++; keyWord++; remaining -= 4;
            }
            // Compare remaining bytes
            while (remaining > 0) {
                if (*(uint8_t*)nodeWord != *(uint8_t*)keyWord) goto keyMismatch;
                nodeWord = (uint32_t*)((uint8_t*)nodeWord + 1);
                keyWord = (uint32_t*)((uint8_t*)keyWord + 1);
                remaining--;
            }
            return; // exact match found
        }
keyMismatch:
        node = node->next;
    }

    // Key not found – insert it via helper function
    FUN_00638840(this, key, length); // insertIntoTable
}