// FUNC_NAME: HashTable::find
// Function address: 0x00573440
// This function performs a hash table lookup. The hash table is stored at this+0x30.
// The table structure: pointer to bucket array, then number of buckets.
// Each bucket is a linked list of nodes with key at offset 0, value at offset 4, next at offset 12.

uint* HashTable::find(uint key) {
    // Get the hash table structure from this+0x30
    // Structure: [bucketArray (pointer), bucketCount (uint)]
    uint** tablePtr = *(uint***)(this + 0x30);
    uint bucketCount = tablePtr[1];
    uint bucketIndex = key % bucketCount;
    uint* bucketHead = tablePtr[0] + bucketIndex * 4; // pointer to first node in bucket
    uint* node = *bucketHead; // dereference to get actual node pointer

    while (node != nullptr) {
        if (node[0] == key) {
            // Found: return pointer to value (node + 1)
            return node + 1;
        }
        node = (uint*)node[3]; // next node (offset 12)
    }
    return nullptr;
}