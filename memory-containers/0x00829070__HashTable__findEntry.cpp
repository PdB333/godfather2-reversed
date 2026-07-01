// FUNC_NAME: HashTable::findEntry
int __thiscall HashTable::findEntry(int this, int* key) {
    // hashData[0] = computed hash, hashData[1] = bucket index, hashData[2] = node pointer
    int hashData[3];

    // Compute hash from the key
    FUN_00828b30(hashData, key);

    // this+0x4: pointer to array of stored keys (or head pointers)
    // this+0x8: number of buckets or selected bucket index
    int* bucketArray = *(int**)(this + 4);
    int bucketIndex = *(int*)(this + 8);
    int storedKey = *(int*)((int)bucketArray + bucketIndex * 4);

    // If the computed hash matches the key stored at this bucket, process further
    if (hashData[0] == storedKey) {
        hashData[0] = *key;                         // Keep the original key value
        int maskedKey = (int)((unsigned int)key & 0xFFFFFF00); // Align key pointer (clear low byte)
        hashData[1] = 0;
        // Retrieve the actual node from bucket using the hash info
        FUN_00828be0(&hashData[2], hashData, maskedKey);
        hashData[0] = hashData[2];
    }

    // Return pointer to the value portion (key at offset 0, value at offset +4)
    return hashData[0] + 4;
}