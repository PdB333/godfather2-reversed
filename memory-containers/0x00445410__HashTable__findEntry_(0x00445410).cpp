// FUNC_NAME: HashTable::findEntry (0x00445410)
// Performs a hash table lookup by key, returning a result structure.

struct HashNode {
    HashNode* next;      // +0x00: next node in bucket linked list
    uint32_t  data;      // +0x04: associated data (interpreted as pointer later)
    // padding or other fields; key at +0x10
    uint32_t  key;       // +0x10: lookup key
};

struct FindResult {
    HashNode* node;      // +0x00: found node pointer (null if not found)
    uint32_t  data;      // +0x04: node->data value
    uint32_t  extra;     // +0x08: additional data derived from node->data (if non-zero)
};

// Global hash table: 4096 buckets, each bucket is a pointer to a linked list
// Address DAT_01162380 in original binary
extern HashNode* gHashBuckets[4096];

// __thiscall: ECX holds the hash table object (not used here, but preserved)
void __thiscall HashTable::findEntry(FindResult& result, const uint32_t& key) {
    uint32_t bucketIdx = key & 0xFFF;               // 12-bit hash
    HashNode* node = gHashBuckets[bucketIdx];        // head of bucket list

    // Walk the linked list to find matching key
    while (node != nullptr && node->key != key) {
        node = node->next;
    }

    result.node  = node;                            // +0x00
    result.extra = 0;                               // +0x08 default

    if (node == nullptr) {
        result.data = 0;                            // +0x04 when not found
    } else {
        result.data = node->data;                   // +0x04
        // If node->data is non-zero, treat it as a pointer and read a value at offset +8
        if (node->data != 0) {
            result.extra = *(uint32_t*)(node->data + 8);
            return;
        }
    }
}