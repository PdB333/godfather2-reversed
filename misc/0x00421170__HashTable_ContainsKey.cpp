// FUNC_NAME: HashTable_ContainsKey

struct HashTableEntry {
    int key0;          // +0x1c
    int key1;          // +0x20
    int key2;          // +0x24
    int key3;          // +0x28
    HashTableEntry* next; // +0x2c
};

struct HashTable {
    HashTableEntry** buckets; // +0x00? (points to raw array)
    int numBuckets;           // +0x04? (second int at DAT_012053ac)
};

// Global hash table instance
extern HashTable* gHashTable; // DAT_012053ac

// Forward declaration of hash function
uint ComputeHash(const int* key); // FUN_004209c0

// Check if a 4-integer key exists in the global hash table.
// If found, the function returns immediately; otherwise does nothing.
void HashTable_ContainsKey(int* key)
{
    bool isNonZero = (key[0] != 0) || (key[1] != 0) || (key[2] != 0) || (key[3] != 0);
    if (!isNonZero) {
        return;
    }

    uint hashVal = ComputeHash(key);
    uint bucketIndex = hashVal % gHashTable->numBuckets;
    HashTableEntry* entry = gHashTable->buckets[bucketIndex];

    while (entry != nullptr) {
        if (entry->key0 == key[0] &&
            entry->key1 == key[1] &&
            entry->key2 == key[2] &&
            entry->key3 == key[3]) {
            return; // Found, indicate existence by early return
        }
        entry = entry->next;
    }
    // Not found, nothing done
    return;
}