//FUNC_NAME: hashTableLookup
// Function at 0x005e7a40: Looks up an entry in a hash table using a hashed key.
// The global DAT_01223504 points to a hash table structure.
// param_1: hashed key (XORed with seed 0xad103100)
// param_2: output buffer for 3 uint32 values (offsets 0x40, 0x44, 0x48 of the entry)
// Returns: low byte = success flag (1 if found, 0 otherwise), upper 24 bits = high 24 bits of the hash.

struct HashTable {
    uint32_t count;          // +0x00? (not used directly)
    uint32_t* entries[256];  // +0x04: array of pointers indexed by (param_1 & 0xFF)
    uint8_t maxIndex;        // +0x1C: maximum valid index for the array
    // ... other fields
};

struct HashEntry {
    uint32_t field0x00;      // +0x00
    uint32_t field0x04;      // +0x04
    // ... up to 0x40
    uint32_t data0;          // +0x40
    uint32_t data1;          // +0x44
    uint32_t data2;          // +0x48
};

uint32_t hashTableLookup(uint32_t param_1, uint32_t* param_2) {
    HashTable* table = (HashTable*)DAT_01223504;
    uint8_t maxIndex = *(uint8_t*)((uint8_t*)table + 0x1C);
    uint32_t hash = param_1 ^ 0xAD103100;
    uint8_t index = (uint8_t)param_1;
    uint8_t found = 0;
    uint32_t entryPtr = 0;

    if (hash < maxIndex && maxIndex != 0 && index < maxIndex) {
        entryPtr = *(uint32_t*)((uint8_t*)table + 4 + index * 4);
        if (entryPtr != 0) {
            found = 1;
        }
    }

    if (found) {
        param_2[0] = *(uint32_t*)(entryPtr + 0x40);
        param_2[1] = *(uint32_t*)(entryPtr + 0x44);
        param_2[2] = *(uint32_t*)(entryPtr + 0x48);
    }

    // Return combined flag and high 24 bits of hash
    return (hash >> 8) | found;
}