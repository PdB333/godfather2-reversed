// FUNC_NAME: EARSHashTable::findOrUpdateEntry
// Address: 0x004e5810
// Searches a hash table for an entry matching the given key (param_1).
// If found, copies data from param_2 (probably transform matrix) and param_3 (velocity/quaternion?)
// into the entry's internal fields. Also writes param_3[3] to some related object.
// Hash table structure: global at DAT_01223398 + 8, bucket array, each bucket has linked list nodes.
// Each node: [0]=key, [4]=pointer to entry data, [8]=next node.
// Entry data layout (offset 0x30 = 16-byte transform, 0x50 = another 16-byte pair, 0x98 = dirty flag).

void HashTableManager::findOrUpdateEntry(uint hashKey, const float* transform, const float* velocityOrQuat)
{
    // Global hash table manager pointer (DAT_01223398)
    // Offsets: +8 -> some internal, +0x4 -> buckets array, +0x8 -> bucket count
    int* managerBase = *reinterpret_cast<int**>(DAT_01223398);
    int* bucketMeta = *reinterpret_cast<int**>(managerBase + 2); // +8? Actually deref base+8 then use
    // The decompile shows: *(int *)(*(int *)(DAT_01223398 + 8) + 4) -> bucket array
    // +8 gives bucket base, +4 -> array, +8 -> count
    int** buckets = *reinterpret_cast<int***>(managerBase + 2); // simplified
    uint bucketCount = *reinterpret_cast<uint*>(managerBase + 2 + 1); // offset 0x8? Not exact
    // Actually from decomp: bucketArray = *(uint **)(*(int *)(DAT_01223398 + 8) + 4);
    // bucketCount = *(uint *)(*(int *)(DAT_01223398 + 8) + 8);
    // So we need to read properly:
    int* hashTableData = *reinterpret_cast<int**>(DAT_01223398 + 8);
    uint** bucketArray = reinterpret_cast<uint**>(hashTableData[1]); // +4
    uint bucketSize = hashTableData[2]; // +8

    uint index = hashKey % bucketSize;
    uint* node = bucketArray[index];

    // Traverse linked list
    while (node != nullptr)
    {
        if (node[0] == hashKey)
        {
            // Found matching node; node[1] points to the data structure (uVar5)
            void* entry = reinterpret_cast<void*>(node[1]);
            // Copy transform data (16 bytes = 4 floats) to offset 0x30 and 0x50 of entry
            float* targetTransform = reinterpret_cast<float*>(reinterpret_cast<char*>(entry) + 0x30);
            targetTransform[0] = transform[0];
            targetTransform[1] = transform[1];
            targetTransform[2] = transform[2];
            targetTransform[3] = transform[3];

            float* targetVelocity = reinterpret_cast<float*>(reinterpret_cast<char*>(entry) + 0x50);
            targetVelocity[0] = velocityOrQuat[0];
            targetVelocity[1] = velocityOrQuat[1];
            targetVelocity[2] = velocityOrQuat[2];
            targetVelocity[3] = velocityOrQuat[3];

            // Write velocityOrQuat[3] to another object's field (e.g., a parent pointer's +0x4c)
            // entry+0x24 is a pointer to another structure
            void* linkedObject = *reinterpret_cast<void**>(reinterpret_cast<char*>(entry) + 0x24);
            if (linkedObject != nullptr)
            {
                *reinterpret_cast<float*>(reinterpret_cast<char*>(linkedObject) + 0x4c) = velocityOrQuat[3];
            }

            // Set dirty flag at offset 0x98
            *reinterpret_cast<char*>(reinterpret_cast<char*>(entry) + 0x98) = 1;

            return;
        }
        node = reinterpret_cast<uint*>(node[2]); // next node
    }

    // If not found, do nothing. The decompiler's 'LAB_004e5843' path appears to set uVar5=0 and then 
    // attempt writes, but that would be null-pointer access; likely the decompiler misread the control flow.
    // The actual intent: only update existing entries.
    return;
}