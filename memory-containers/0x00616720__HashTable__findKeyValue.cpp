// FUNC_NAME: HashTable::findKeyValue
// Function at 0x00616720: Looks up a key in a hash table (likely ID-to-handle mapping) and returns the associated value.
// The global structure at DAT_01205968 holds the hash table configuration (bucket count at +0x808, bucket array at +0x80c).
// The key is passed via ESI (implicit parameter).
// Returns the value at node->value as uint32_t, or 0xFFFFFFFF if not found.

#include <cstdint>

// Hash table node layout (each node is a linked list element)
struct HashNode {
    uint32_t key;        // +0x00: the key being hashed
    void* value;         // +0x04: associated value (interpreted as uint32_t on return)
    HashNode* next;      // +0x08: next node in the bucket chain
};

// Global hash table manager (assumed to be a singleton)
struct HashTableManager {
    uint8_t pad_0x000[0x808];            // padding up to offset 0x808
    uint32_t numBuckets;                 // +0x808: number of buckets in the hash table
    HashNode** bucketArray;              // +0x80c: pointer to array of bucket head pointers (HashNode*)
};

extern HashTableManager* g_hashTableManager;  // DAT_01205968

// __fastcall? Actually key is passed in ESI – we model as a normal parameter for readability.
uint32_t HashTableFindKey(uint32_t key) {
    uint32_t bucketIndex = key % g_hashTableManager->numBuckets;
    HashNode* currentNode = g_hashTableManager->bucketArray[bucketIndex];

    if (currentNode == nullptr) {
        return 0xFFFFFFFF;
    }

    // Traverse the linked list in the bucket
    while (currentNode->key != key) {
        currentNode = currentNode->next;
        if (currentNode == nullptr) {
            return 0xFFFFFFFF;
        }
    }

    // Key found: return the value stored at offset 0x04 (interpreted as uint32_t)
    if (currentNode->value != nullptr) {
        return *reinterpret_cast<uint32_t*>(currentNode->value);
    }

    return 0xFFFFFFFF;
}