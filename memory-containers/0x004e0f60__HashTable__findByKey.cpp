// FUNC_NAME: HashTable::findByKey
// Address: 0x004e0f60
// Role: Look up a 16-byte (4-int) key in a hash table with per-bucket linked lists.
// Hash table structure: [0x00] bucket array pointer, [0x04] number of buckets.
// Node structure: [0x00] pointer to 16-byte key, [0x04] unknown (probably hash cache), [0x08] next node pointer.

struct HashNode {
    int* key;          // +0x00
    int  unknown;      // +0x04 (reserved)
    HashNode* next;    // +0x08
};

struct HashTable {
    HashNode** buckets; // +0x00
    int        numBuckets; // +0x04
};

HashNode* __thiscall HashTable::findByKey(HashTable* this, int* key) {
    HashNode* node;
    int* nodeKey;
    uint hash = 0;

    // Compute hash over the 16 bytes (4 ints) of the key.
    if (key != nullptr) {
        for (byte* p = (byte*)key; p < (byte*)(key + 4); ++p) {
            hash = hash * 0x1003f + (uint)(*p);
        }
    }

    // Probe the bucket chain.
    node = this->buckets[hash % this->numBuckets];
    while (node != nullptr) {
        nodeKey = node->key;
        // Compare the 4 ints of the key.
        if (nodeKey[0] == key[0] &&
            nodeKey[1] == key[1] &&
            nodeKey[2] == key[2] &&
            nodeKey[3] == key[3]) {
            return node; // found – returns node pointer
        }
        node = node->next;
    }
    return nullptr; // not found
}