// FUNC_NAME: HashTable::lookup
uint HashTable::lookup(uint key) {
    // Global pointer to hash table singleton, DAT_01223398
    // The internal data structure lies at offset 0x8 of the global.
    // Internal structure (HashTableData):
    //   +0x00: unknown
    //   +0x04: bucket array pointer (uint**)
    //   +0x08: table size (modulus)
    struct HashNode {
        uint key;        // +0x00
        uint value;      // +0x04
        HashNode* next;  // +0x08
    };

    uint** dataPtr = *(uint***)(DAT_01223398 + 8);
    uint tableSize = (uint)(dataPtr[2]);        // +0x08
    uint* bucketArray = (uint*)(dataPtr[1]);    // +0x04

    uint index = key % tableSize;
    HashNode* node = (HashNode*)bucketArray[index];

    while (node != nullptr) {
        if (node->key == key) {
            // Original had a redundant check node+1 != nullptr; omitted
            return node->value;
        }
        node = node->next;
    }
    return 0;
}