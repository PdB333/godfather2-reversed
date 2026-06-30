// FUNC_NAME: HashTable::lookup

int __thiscall HashTable::lookup(int this, int key) {
    // Null checks for this and the hash table pointer at +0x70
    if (this == 0 || *(int *)(this + 0x70) == 0) {
        return -1;
    }
    // Get hash table structure (pointer at +0x70)
    int hashTable = *(int *)(this + 0x70);
    // Buckets array at +0x1c within hashTable
    int buckets = *(int *)(hashTable + 0x1c);
    // Bucket index stored as short at +0x74
    short bucketIndex = *(short *)(this + 0x74);
    // Each bucket is 0x18 bytes; +0x14 is pointer to first entry of chain
    int firstEntry = *(int *)(buckets + bucketIndex * 0x18 + 0x14);
    // Search chain for key; returns index into the chain array if found, else -1
    int index = FUN_005828a0(key, firstEntry);
    if (index == -1) {
        return -1;
    }
    // Each entry is 0x14 bytes; value stored at +0x10
    int value = *(int *)(firstEntry + 0x10 + index * 0x14);
    if (value == -1) {
        return -1;
    }
    return value;
}