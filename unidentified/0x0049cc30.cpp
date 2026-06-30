// FUNC_ADDR: 0x0049cc30
// ROLE: Resize/rehash a hash table (increase bucket count, redistribute entries)
// Struct: HashTable: [0x00] buckets (void**), [0x04] size (int)
// HashNode layout: +0x08 hashKey (uint), +0x14 next (HashNode*)

#include <cstring>

class HashTable {
public:
    void** buckets;   // +0x00
    int size;          // +0x04

    void rehash();
};

void HashTable::rehash() {
    int newSize = size * 2 + 1;

    // Allocate new bucket array and zero it
    void** newBuckets = new void*[newSize];
    memset(newBuckets, 0, newSize * sizeof(void*));

    // Iterate over all old buckets
    for (int bucketIdx = 0; bucketIdx < size; ++bucketIdx) {
        // Walk the linked list in this bucket
        HashNode* entry = static_cast<HashNode*>(buckets[bucketIdx]);
        while (entry) {
            uint newIndex = entry->hashKey % newSize;
            HashNode* nextEntry = entry->next;

            // Insert at head of new bucket
            entry->next = static_cast<HashNode*>(newBuckets[newIndex]);
            newBuckets[newIndex] = entry;

            entry = nextEntry;
        }
    }

    // Free old bucket array and update table
    delete[] buckets;
    buckets = newBuckets;
    size = newSize;
}