// FUNC_NAME: EntityDataManager::findAndProcessEntity
void EntityDataManager::findAndProcessEntity(int entityId) {
    byte stepFlag;
    char stepSize;
    char currentIndex;
    char bucketCount;
    char iterationCount;
    int *ptr;
    
    if (this != nullptr) {
        // Determine step size from some global state flag
        stepFlag = (*(byte *)(*(int *)(this + 8) + 8) & 1) != 0;  // m_pSomeFlag +0x08 bit0
        stepSize = stepFlag + 1;  // step is 1 or 2
        
        // Starting index for linear probe (wraps around bucket count)
        currentIndex = *(char *)(this + 0x6e) - stepSize;  // m_lastUsedBucket
        if (currentIndex < 0) {
            currentIndex += *(char *)(this + 0x6f);  // m_numBuckets
        }
        bucketCount = *(byte *)(this + 0x6f);  // m_numBuckets
        iterationCount = 0;
        
        if (bucketCount != 0) {
            // Linear probe to find the bucket containing entityId
            while (true) {
                if ((char)bucketCount <= currentIndex) {
                    currentIndex = currentIndex - bucketCount;
                }
                ptr = *(int **)(this + 0x0c + currentIndex * 4);  // m_buckets[currentIndex]
                if ((ptr != nullptr) && (*(int *)(ptr + 8) == entityId)) {  // ptr->m_entityId at +0x20? wait offset 0x20 from ptr, but ptr is int*, so ptr+8 is offset 0x20? Actually ptr is int*, so ptr+8 means offset 0x20 (8*4). But the decompiled shows *(int *)(iVar5 + 0x20) == param_1. So ptr+0x20. Here iVar5 is ptr, so ptr[8] = entityId.
                // In the decompiled: *(int *)(iVar5 + 0x20) == param_1. So yes, offset 0x20.
                    break;
                }
                iterationCount += stepSize;
                currentIndex += stepSize;
                if ((int)(uint)bucketCount <= (int)iterationCount) {
                    return;
                }
            }
            
            // Process the found entity and its companion(s) using secondary pointer array
            // This loop iterates 'stepFlag+1' times (i.e., 1 or 2 times), processing objects from the secondary array
            do {
                if ((ptr != nullptr) && ((*(byte *)(ptr + 4) & 0x40) == 0)) {  // ptr->m_flags at +0x10? offset 0x10
                    // Call a virtual function on the object (likely destroy/update) via a global vtable
                    (**(code **)(*DAT_01223510 + 0x24))(*(undefined2 *)(ptr + 2));  // pass object's handle at +0x08 as 16-bit
                    FUN_005dbc10(*(undefined2 *)(ptr + 2), *(undefined4 *)(ptr + 6));  // additional cleanup
                    FUN_005f1660();  // possibly a global update
                }
                stepFlag--;
                ptr = *(int **)(this + 0x10 + currentIndex * 4);  // m_secondary[currentIndex] or m_next[currentIndex]
            } while (-1 < stepFlag);
        }
    }
    return;
}