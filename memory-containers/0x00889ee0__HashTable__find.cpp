// FUNC_NAME: HashTable::find
int __thiscall HashTable::find(uint *keyPtr) {
    int nodePtr;
    uint key;
    // Local struct for hash key (size 0x20? based on local variables)
    struct HashKey {
        uint key;          // +0x00
        uint field_4;      // +0x04 (unused, zero)
        uint field_8;      // +0x08 (unused, zero)
        uint field_C;      // +0x0C (unused, zero)
        uint field_10;     // +0x10 (unused, zero)
        uint field_14;     // +0x14 (unused, zero)
        uint field_18;     // +0x18 (unused, zero)
        uint field_1C;     // +0x1C (unused, zero)
    } hashKey;

    int bucketCount = *(int *)(this + 0x80); // +0x80: number of buckets
    key = *keyPtr;

    // Initialize hash key struct
    hashKey.key = key;
    hashKey.field_4 = 0;
    hashKey.field_8 = 0;
    hashKey.field_C = 0;
    hashKey.field_10 = 0;
    hashKey.field_14 = 0;
    hashKey.field_18 = 0;
    hashKey.field_1C = 0;
    // Note: local_64 is actually the start of hashKey, but Ghidra misinterprets the AND.
    // The actual code likely does: hashKey.key = key; hashKey.field_4 = 1; etc.
    // Based on local_50 = 1, that might be a type/size field.
    // We'll assume field_4 is set to 1 (type indicator).
    hashKey.field_4 = 1; // +0x04: type/size (1 = uint key?)

    // Call hash lookup function: returns pointer to node in bucket
    nodePtr = FUN_00889090(*(undefined4 *)(this + 0x7c), bucketCount, &hashKey, hashKey.key);
    // Note: the 4th argument is hashKey.key, but the function signature may expect the whole struct.

    // If returned node is not the sentinel (bucketCount) and its stored key matches input key
    if ((nodePtr == bucketCount) || (key < *(uint *)(nodePtr + 8))) {
        nodePtr = bucketCount; // sentinel value
    }

    if (nodePtr == bucketCount) {
        return 0; // not found
    }
    return nodePtr; // found, return pointer to node
}