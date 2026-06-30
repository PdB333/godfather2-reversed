// FUNC_NAME: hash16ByteKeyToIndex
// Function address: 0x004e0dd0
// Computes a hash over a 16-byte key and returns an index into a hash table.
// param_1: pointer to 16-byte key (e.g., GUID or object ID)
// param_2: pointer to hash table structure; offset +0x4 contains the table size (modulus)
uint __thiscall hash16ByteKeyToIndex(uint8_t *key, void *hashTable)
{
    uint hash = 0;
    uint8_t *end = key + 0x10; // process exactly 16 bytes

    if (key != nullptr && key < end) {
        do {
            hash = hash * 0x1003f + *key; // classic djb2-style hash
            key++;
        } while (key < end);
    }

    // Return index modulo table size (stored at hashTable+4)
    return hash % *(uint *)((uint8_t *)hashTable + 4);
}