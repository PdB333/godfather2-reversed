// FUNC_NAME: MotionDataManager::UpdateMotionDataByKey
void __thiscall MotionDataManager::UpdateMotionDataByKey(uint key, float* data) {
    // Global singleton pointer (+0x8 is pointer to hash table structure)
    int* hashTableStruct = *(int**)(*(int*)(DAT_01223398 + 8) + 4);
    int bucketCount = *(int*)(*(int*)(DAT_01223398 + 8) + 8);
    uint bucketIndex = key % bucketCount;
    uint** bucket = (uint**)(hashTableStruct + bucketIndex * 4); // each bucket is a linked list node pointer

    uint* node = *bucket;
    while (node != nullptr) {
        if (*node == key) {
            // Found existing entry – node[1] points to data block
            uint dataPtr = node[1];
            // Copy 10 floats into the data block at specific offsets
            *(float*)(dataPtr + 0x30) = data[4];
            *(float*)(dataPtr + 0x34) = data[5];
            *(float*)(dataPtr + 0x38) = data[6];
            *(float*)(dataPtr + 0x3C) = data[7];
            *(float*)(dataPtr + 0x70) = data[0];
            *(float*)(dataPtr + 0x74) = data[1];
            *(float*)(dataPtr + 0x78) = data[2];
            *(float*)(dataPtr + 0x7C) = data[3];
            *(float*)(dataPtr + 0x8C) = data[8];
            *(float*)(dataPtr + 0x84) = data[9];
            *(uint8*)(dataPtr + 0x98) = 1;
            return;
        }
        node = (uint*)node[2];
    }

    // Note: If key not found, the original code would attempt to write to null
    // (uVar5 = 0), indicating this function expects the entry to already exist.
    // The crash is avoided if the caller ensures the key is present.
    // For safety, we do nothing.
}