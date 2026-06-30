// FUNC_NAME: HashTable::findEntry
// Address: 0x00655250
// Searches a hash table for an entry matching a 12-byte key (short[6]).
// The hash table is stored at this+0x20 (bucket array) with size at this+0x18.
// Returns pointer to matching entry or 0 if not found.

uint32 HashTable::findEntry(short *key)
{
    uint32 hash;
    int bucketArray;
    int entry;
    int in_EAX; // this pointer

    // Compute hash from the 12-byte key (short[6] = 12 bytes)
    // Hash = ((((key[2] << 8 ^ key[1]) * 8 ^ key[3]) << 5 ^ key[2] >> 16 ^ key[0]) % tableSize
    hash = ((((*(uint32 *)(key + 4) << 8 ^ (uint32)(uint16)key[1]) * 8 ^
             *(uint32 *)(key + 6)) << 5 ^ *(uint32 *)(key + 4) >> 0x10 ^
            *(uint32 *)(key + 2)) % *(uint32 *)(in_EAX + 0x18)); // +0x18 = tableSize

    bucketArray = *(int *)(in_EAX + 0x20); // +0x20 = bucket array pointer
    entry = *(int *)(bucketArray + hash * 4);

    while (true) {
        if (entry == 0) {
            return 0; // empty bucket -> not found
        }

        entry = *(int *)(bucketArray + hash * 4);

        // Compare all 6 shorts of the key (12 bytes total)
        if ((((*key == *(short *)(entry + 0x100)) &&
              (key[1] == *(uint16 *)(entry + 0x102))) &&
             (*(int *)(key + 2) == *(int *)(entry + 0x104))) &&
            (((*(int *)(key + 4) == *(int *)(entry + 0x108)) &&
              (*(int *)(key + 6) == *(int *)(entry + 0x10c))) &&
             (*(int *)(key + 8) == *(int *)(entry + 0x110))))
            break; // found matching entry

        hash = hash + 1;
        if (*(uint32 *)(in_EAX + 0x18) <= hash) { // wrap around
            hash = 0;
        }
        entry = *(int *)(bucketArray + hash * 4);
    }

    return *(uint32 *)(bucketArray + hash * 4); // return pointer to entry
}