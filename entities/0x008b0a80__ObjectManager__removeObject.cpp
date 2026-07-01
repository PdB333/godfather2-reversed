// FUNC_NAME: ObjectManager::removeObject
void __thiscall ObjectManager::removeObject(int thisPtr, int objectPtr)
{
    uint flatIndex = 0;
    uint flatCount = *(uint *)(thisPtr + 0x20);
    if (flatCount == 0) return;

    int *flatArray = *(int **)(thisPtr + 0x1c);
    // Find object in flat list
    while (*flatArray != objectPtr) {
        flatIndex++;
        flatArray++;
        if (flatIndex >= flatCount) return;
    }

    int bucketCount = *(int *)(thisPtr + 0x08);
    if (bucketCount > 0) {
        int *bucketArray = *(int **)(thisPtr + 0x04);
        // Iterate buckets backwards
        for (int bucketIdx = bucketCount - 1; bucketIdx >= 0; bucketIdx--) {
            int *bucket = (int *)bucketArray[bucketIdx];
            uint bucketElemCount = *(uint *)(bucket + 8); // +0x08
            if (bucketElemCount > 0) {
                int *bucketElemArray = *(int **)(bucket + 4); // +0x04
                for (uint elemIdx = 0; elemIdx < bucketElemCount; elemIdx++) {
                    if (bucketElemArray[elemIdx] == objectPtr) {
                        // Remove from bucket: shift last element into this slot
                        if (elemIdx != bucketElemCount - 1) {
                            bucketElemArray[elemIdx] = bucketElemArray[bucketElemCount - 1];
                        }
                        *(int *)(bucket + 8) = bucketElemCount - 1;
                        goto removedFromBucket;
                    }
                }
            }
        }
    }
removedFromBucket:
    // Remove from flat list: shift last element into this slot
    if (flatIndex != flatCount - 1) {
        int *flatArrayBase = *(int **)(thisPtr + 0x1c);
        flatArrayBase[flatIndex] = flatArrayBase[flatCount - 1];
    }
    *(int *)(thisPtr + 0x20) = flatCount - 1;
}