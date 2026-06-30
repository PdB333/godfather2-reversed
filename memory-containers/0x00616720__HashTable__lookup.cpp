// FUNC_NAME: HashTable::lookup
uint HashTable::lookup(uint key) {
    uint* bucket;
    uint index;

    // Calculate bucket index using hash modulo table size
    index = key % *(uint*)(DAT_01205968 + 0x808);
    bucket = *(uint**)(*(int*)(DAT_01205968 + 0x80c) + index * 4);

    if (bucket != nullptr) {
        // Walk the linked list in this bucket
        while (*bucket != key) {
            bucket = (uint*)bucket[2]; // next pointer at +0x08
            if (bucket == nullptr) {
                return 0xffffffff; // Not found
            }
        }
        // Found: return value at offset +0x04
        if (*(undefined4*)bucket[1] != nullptr) {
            return *(uint*)bucket[1];
        }
    }
    return 0xffffffff; // Not found
}