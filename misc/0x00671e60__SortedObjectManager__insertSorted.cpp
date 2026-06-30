// FUNC_NAME: SortedObjectManager::insertSorted
int SortedObjectManager::insertSorted(int objectId) {
    unsigned short bucketCount = *(unsigned short *)(this + 0x10);
    unsigned int bucketIndex = 0;
    if (bucketCount == 0) {
        // Allocate first bucket
        int *newBucket = (int *)FUN_00673070();
        *(int *)(this + 0x14) = newBucket;
        if (newBucket != 0) {
            int *newItemArray = (int *)FUN_00673070();
            *(int *)(*(int *)(this + 0x14) + 4) = newItemArray;
            if (*(int *)(*(int *)(this + 0x14) + 2) != 0) { // ??? This check seems off; likely a bug in decompilation. Possibly the structure has a different layout. We'll follow the logic.
                *(short *)(*(int *)(this + 0x14)) = 1; // Set bucket count to 1
                *(short *)(*(int *)(this + 0x14) + 4) = (short)objectId; // Store objectId in first item
                *(short *)(this + 0x10) = *(short *)(this + 0x10) + 1; // Increment bucket count
                return 0;
            }
        }
        return 0x2718; // Allocation failed
    }
    bool found = false;
    bool insertBefore = false;
    unsigned int bestBucketIndex = 0;
    // Iterate through buckets
    for (unsigned int i = 0; i < bucketCount; i++) {
        short itemCount = *(short *)(*(int *)(this + 0x14) + i * 8);
        int *itemArray = *(int **)(*(int *)(this + 0x14) + i * 8 + 2);
        // Iterate through items in bucket
        for (unsigned int j = 0; j < (unsigned int)itemCount && !found; j++) {
            int *dataA = (int *)(this + 0x0C) + objectId * 0xC4 / 4; // Actually objectId * 0xC4 + *(int *)(this+0x0C)
            int *dataB = (int *)(this + 0x0C) + (*(unsigned short *)(itemArray + j)) * 0xC4 / 4;
            char *nameA = (char *)(dataA + 1); // Offset 4
            char *nameB = (char *)(dataB + 1);
            short flagA = *(short *)(dataA + 0x44 / 4); // Offset 0x44
            short flagB = *(short *)(dataB + 0x44 / 4);
            bool bothNamesEmpty = (*nameA == '\0' && *nameB == '\0');
            bool bothFlagsZero = (flagA == 0 && flagB == 0);
            if (bothNamesEmpty || bothFlagsZero) {
                found = false;
            } else {
                found = true;
            }
            // Determine ordering based on name and flag
            bool orderFlag;
            if (bothNamesEmpty && bothFlagsZero) {
                orderFlag = true;
            } else if (*nameA == '\0' && *nameB == '\0') {
                orderFlag = true;
            } else if (*nameA == '\0' && flagB == 0) {
                orderFlag = false;
            } else if (flagA == 0 && *nameB == '\0') {
                orderFlag = false;
            } else {
                // Lexicographic compare
                orderFlag = (strcmp(nameA, nameB) < 0);
            }
            if (orderFlag) {
                found = true;
                bestBucketIndex = i;
            }
        }
    }
    if (!found) {
        // Need to create a new bucket
        if (bucketCount < someLimit?) { // Not checked here, but does reallocation
            int *newBucketArray = (int *)FUN_006730f0(*(int *)(this + 0x14), bucketCount * 8);
            *(int *)(this + 0x14) = newBucketArray;
            if (newBucketArray == 0) {
                return 0x271e;
            }
            int *newItemArray = (int *)FUN_00673070();
            *(int *)(*(int *)(this + 0x14) + 4 + bucketCount * 8) = newItemArray;
            if (*(int *)(*(int *)(this + 0x14) + 4 + bucketCount * 8) == 0) {
                *(short *)(this + 0x10) = *(short *)(this + 0x10) + 1;
                return 0x2718;
            }
            *(short *)(*(int *)(this + 0x14) + bucketCount * 8) = 1; // Set count to 1
            *(short *)(*(int *)(this + 0x14) + 4 + bucketCount * 8) = (short)objectId;
            *(short *)(this + 0x10) = *(short *)(this + 0x10) + 1;
            return 0;
        }
    } else {
        // Insert into existing bucket
        int *itemArray = *(int **)(*(int *)(this + 0x14) + bestBucketIndex * 8 + 4);
        int newSize = *(short *)(*(int *)(this + 0x14) + bestBucketIndex * 8) * 4;
        int *newItemArray = (int *)FUN_006730f0(itemArray, newSize);
        *(int *)(*(int *)(this + 0x14) + 4 + bestBucketIndex * 8) = newItemArray;
        if (newItemArray == 0) {
            return 0x271e;
        }
        int count = *(short *)(*(int *)(this + 0x14) + bestBucketIndex * 8);
        *(short *)(newItemArray + count) = (short)objectId;
        *(short *)(*(int *)(this + 0x14) + bestBucketIndex * 8) = count + 1;
        return 0;
    }
    return 0; // Should not reach
}