// FUNC_NAME: EntityManager::setTransformData
void EntityManager::setTransformData(uint objectId, uint* data) {
    // Global hash table structure at DAT_01223398
    // Structure: +0x0: unknown, +0x4: bucket array pointer, +0x8: bucket count
    HashTable* hashTable = *(HashTable**)(DAT_01223398 + 8);
    uint bucketCount = hashTable->bucketCount;
    uint bucketIndex = objectId % bucketCount;
    HashNode* node = hashTable->buckets[bucketIndex];

    while (node) {
        if (node->key == objectId) {
            // Found existing object, use its pointer
            uint objectPtr = node->value;
            if (objectPtr != 0) {
                // Copy 4 uint32 values to object at offset 0x30
                *(uint*)(objectPtr + 0x30) = data[0];
                *(uint*)(objectPtr + 0x34) = data[1];
                *(uint*)(objectPtr + 0x38) = data[2];
                *(uint*)(objectPtr + 0x3C) = data[3];
                // Set dirty/updated flag at offset 0x98
                *(byte*)(objectPtr + 0x98) = 1;
            }
            return;
        }
        node = node->next;
    }

    // Object not found, do nothing (or create new? but code sets uVar5=0 and then writes to 0x30 which would crash)
    // Actually the original code sets uVar5=0 and then writes to uVar5+0x30, which would be null pointer write.
    // This is likely a bug or decompiler artifact; we assume object must exist.
    // For safety, we skip writing if not found.
    return;
}