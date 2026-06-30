// FUNC_NAME: HashTable::removeEntry
// Address: 0x004e0c20
// Removes an entry from a 16-byte key hash table. Moves the node to a free list.
// Input: this (HashTable*) in EDI, key (16-byte key) in ESI
// Returns: 0 on success, 1 if key not found

struct HashTable;
struct HashNode;
struct KeyBlock;

struct KeyBlock {
    uint32_t keyData[4];     // +0x00: the 16-byte key
    HashNode* nextNode;      // +0x10: pointer to next HashNode (unused in this function)
};

struct HashNode {
    KeyBlock* keyBlock;      // +0x00: pointer to the key block
    HashNode* next;          // +0x04: next node in the bucket chain
};

struct HashTable {
    HashNode** buckets;      // +0x00: array of bucket heads
    int bucketCount;         // +0x04: number of buckets
    HashNode* freeList;      // +0x08: head of free list
    int freeCount;           // +0x0C: count of free nodes
};

int __fastcall HashTable::removeEntry(this, keyPtr)
{
    HashTable* ht = reinterpret_cast<HashTable*>(this);   // in EDI
    uint32_t* key = reinterpret_cast<uint32_t*>(keyPtr); // in ESI

    // Compute hash over 16 bytes (4 uint32s)
    uint32_t hash = 0;
    if (key != nullptr) {
        for (int i = 0; i < 4; ++i) {
            hash = hash * 0x1003f + key[i];
        }
    }

    int bucketIndex = hash % ht->bucketCount;
    HashNode** bucketPtr = &ht->buckets[bucketIndex];
    HashNode* curr = *bucketPtr;
    HashNode* prev = nullptr;

    if (curr == nullptr) {
        return 1;  // bucket empty -> not found
    }

    while (true) {
        HashNode* node = curr;   // node at *bucketPtr (or from previous iteration)
        
        // Get the key data pointer from the key block (offset 0x10 of keyBlock)
        uint32_t* storedKey = reinterpret_cast<uint32_t*>(node->keyBlock->nextNode); // actually +0x10 field
        // Compare storedKey[0..3] with key[0..3]
        if (storedKey[0] == key[0] && storedKey[1] == key[1] &&
            storedKey[2] == key[2] && storedKey[3] == key[3]) {
            // Found – remove from bucket chain
            if (prev == nullptr) {
                *bucketPtr = node->next;
            } else {
                prev->next = node->next;
            }
            // Move node to free list
            node->next = ht->freeList;
            ht->freeList = node;
            ht->freeCount--;
            return 0;  // success
        }

        prev = node;
        curr = node->next;  // next node in chain (from node+0x04)
        if (curr == nullptr) {
            return 1;  // end of chain -> not found
        }
    }
}