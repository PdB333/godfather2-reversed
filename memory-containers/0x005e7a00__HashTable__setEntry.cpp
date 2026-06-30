// FUNC_NAME: HashTable::setEntry
// Function at 0x005e7a00: Sets a value (param_2) at offset 0x68 of an object identified by a hashed ID (param_1).
// Uses a global hash table with 256 buckets (pointers at base+4) and a count at base+0x1c.
// Returns 1 on success, 0 on failure.

#include <cstdint>

// Global hash table structure (singleton)
struct HashTable {
    uint32_t count;          // +0x1c: number of entries? (compared with full hash)
    void* buckets[256];      // +0x04: array of pointers to objects
};

// Global pointer to the hash table (DAT_01223504)
extern HashTable* g_hashTable;

// Hash constant
const uint32_t HASH_SEED = 0xad103100;

bool setHashTableEntry(uint32_t id, uint32_t value) {
    uint32_t hash = id ^ HASH_SEED;

    // Check if hash is within valid range (count field)
    if (hash < g_hashTable->count) {
        // Use low byte of hash as index into bucket array
        uint32_t index = hash & 0xFF;
        void* obj = g_hashTable->buckets[index];
        if (obj != nullptr) {
            // Write value at offset 0x68 of the object
            *(uint32_t*)((uint8_t*)obj + 0x68) = value;
            return true;
        }
    }
    return false;
}