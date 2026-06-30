// FUNC_NAME: hashTableLookup
#include <cstdint>

// Global hash table structure (static data)
// DAT_012053ac[0]: pointer to bucket array (each entry is a linked list node pointer)
// DAT_012053ac[1]: number of buckets (hash table size)
extern uint32_t gHashTableBase[]; // base address: 0x012053ac, interpreted as two uint32_t: bucketArrayPtr, bucketCount

// Node structure in the hash table (linked list per bucket)
// Offsets relative to node pointer:
// +0x14: value (4 bytes) - the data associated with the key
// +0x1c: key part 0 (4 bytes)
// +0x20: key part 1 (4 bytes)
// +0x24: key part 2 (4 bytes)
// +0x28: key part 3 (4 bytes)
// +0x2c: next pointer (4 bytes) - next node in bucket chain
struct HashNode {
    uint32_t value;          // +0x14
    uint32_t key[4];         // +0x1c to +0x28
    HashNode* next;          // +0x2c
};

// Hash function for 128-bit key (4 uint32)
// FUN_004209c0 - computes a hash from the 4 integers
uint32_t computeHash(const uint32_t key[4]);

// Global hash table lookup
// param_1: pointer to a 128-bit key (4 consecutive uint32)
// Returns: value associated with key, or 0 if not found
uint32_t hashTableLookup(const uint32_t key[4]) {
    // Quick check: if key is null or all zero, no match
    if (key == nullptr) return 0;
    if (key[0] == 0 && key[1] == 0 && key[2] == 0 && key[3] == 0)
        return 0;

    // Compute hash and get bucket index
    uint32_t hash = computeHash(key);
    uint32_t bucketIndex = hash % gHashTableBase[1]; // bucketCount
    HashNode* bucketHead = reinterpret_cast<HashNode*>(gHashTableBase[0]); // base of bucket array? No, bucketArray is an array of pointers, so gHashTableBase[0] points to an array of HashNode*
    HashNode** bucketArray = reinterpret_cast<HashNode**>(gHashTableBase[0]); // treat as pointer to array of pointers
    HashNode* node = bucketArray[bucketIndex];

    // Traverse linked list in the bucket
    while (node != nullptr) {
        // Compare 128-bit key
        if (node->key[0] == key[0] &&
            node->key[1] == key[1] &&
            node->key[2] == key[2] &&
            node->key[3] == key[3]) {
            // Found, return the stored value
            return node->value;
        }
        node = node->next;
    }

    // Not found
    return 0;
}