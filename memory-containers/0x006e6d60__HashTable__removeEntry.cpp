// FUNC_NAME: HashTable::removeEntry

// 006e6d60 - Hash table removal by 128-bit key

struct HashNode {
    int* data;          // +0x00: pointer to data block (key at data+0x10)
    HashNode* next;     // +0x04: next node in chain
};

struct HashTable {
    HashNode** buckets; // +0x00: array of bucket heads
    int bucketCount;    // +0x04: number of buckets
    HashNode* freeList; // +0x08: head of free list (reusable nodes)
    int activeCount;    // +0x0c: number of active entries
};

// Hash function on 16 bytes (from 0x004db320)
extern int hash16(const void* data, int size);

// Debug/validation stub (0x004d9af0)
extern void debugCheck();

int __thiscall HashTable::removeEntry(HashTable* this, const int key[4]) {
    // Copy the 4-word key into a temporary array for hashing
    int keyBuf[4] = { key[0], key[1], key[2], key[3] };

    debugCheck(); // possibly a null/validity assertion

    int hashIndex = hash16(&keyBuf, 16) % this->bucketCount;
    HashNode* bucketHead = this->buckets[hashIndex];

    // Empty bucket
    if (bucketHead == nullptr) {
        return 1; // not found
    }

    HashNode* prev = nullptr;
    HashNode* current = bucketHead;

    while (current != nullptr) {
        // Compare 4 ints at data+0x10, +0x14, +0x18, +0x1c
        int* data = current->data;
        if (data[4] == key[0] && data[5] == key[1] &&
            data[6] == key[2] && data[7] == key[3]) {
            // Found: unlink from bucket chain
            if (prev == nullptr) {
                this->buckets[hashIndex] = current->next;
            } else {
                prev->next = current->next;
            }

            // Move node to free list
            current->next = this->freeList;
            this->freeList = current;
            this->activeCount--;

            return 0; // success
        }
        prev = current;
        current = current->next;
    }

    return 1; // not found
}