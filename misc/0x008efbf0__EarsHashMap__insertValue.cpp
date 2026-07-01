// FUNC_NAME: EarsHashMap::insertValue
// Address: 0x008efbf0
// Purpose: Insert a value into a hash map with capacity checking and optional removal of low-priority nodes.

int __thiscall EarsHashMap::insertValue(int this, int key, int value, bool bInsert)
{
    int nodeCount;
    int hashIndex;
    int currentCount;
    int maxCapacity;
    int capacityLimit;
    int remainingSlots;
    int sentinelHead;
    int *iteratorPtr;
    int localKey;
    int localHash;
    int comparisonResult;
    int searchCount;
    int removedNodeCount;
    int clearBucketIdx;
    int result;
    bool bucketCleared;

    // Check if count (offset +0x14) is within capacity (offset +0x18)
    maxCapacity = *(int *)(this + 0x18);
    currentCount = *(int *)(this + 0x14);
    if ((unsigned int)maxCapacity <= (unsigned int)currentCount) {
        // Already at capacity, attempt to free a slot
        hashIndex = *(int *)(this + 0x30);
        iteratorPtr = (int *)FUN_008ec930(&localKey, &key); // Possibly get bucket iterator
        if ((*iteratorPtr == 0) || (*iteratorPtr != this + 0x2c)) {
            FUN_00b97aea(); // Assertion failed
        }
        if (iteratorPtr[1] == hashIndex) {
            // Validate second iterator (offset +0x20)
            hashIndex = *(int *)(this + 0x24);
            iteratorPtr = (int *)FUN_008ec930(&localKey, &key);
            if ((*iteratorPtr == 0) || (*iteratorPtr != this + 0x20)) {
                FUN_00b97aea();
            }
            if (iteratorPtr[1] == hashIndex) {
                // Count nodes with priority > 2 from the linked list (head at +0x10)
                removedNodeCount = 0;
                sentinelHead = **(int **)(this + 0x10); // Dereference head pointer
                localKey = this + 0xc; // Tail sentinel
                while (true) {
                    // Verify iterator validity (should point to tail sentinel)
                    if (localKey == 0 || localKey != this + 0xc) {
                        FUN_00b97aea();
                    }
                    // Check if we've looped back to head
                    if (sentinelHead == *(int *)(this + 0x10)) break;
                    // Additional sanity checks
                    if (localKey == 0) {
                        FUN_00b97aea();
                    }
                    if (sentinelHead == *(int *)(localKey + 4)) { // Next pointer
                        FUN_00b97aea();
                    }
                    // Count nodes with field at +0x18 > 2 (priority?)
                    if (*(int *)(sentinelHead + 0x18) > 2) {
                        removedNodeCount++;
                    }
                    FUN_008ea1d0(); // Advance iterator
                }

                // Calculate remaining slots after counting removable nodes
                capacityLimit = *(int *)(this + 0x34);
                remainingSlots = (capacityLimit - removedNodeCount) + currentCount;
                if ((unsigned int)maxCapacity <= (unsigned int)remainingSlots) {
                    // Need to remove one node to make room
                    FUN_008ec760(&localHash, value, &searchCount); // Create hash from value
                    FUN_008ec640(&removedNodeCount, key, &localKey); // Insert key/value mapping? Note: removedNodeCount is reused as pointer.

                    // Check if hash is invalid (-0x1e98fd1 ≈ 0xFFE1672F) or bucket count is insufficient
                    if ((localHash == -0x1e98fd1) || (localKey < searchCount)) {
                        // Handle capacity overflow
                        if (removedNodeCount != -0x1e98fd1) {
                            FUN_008ef150(&removedNodeCount);
                            int listSize = FUN_008eabb0(); // Likely get list size
                            if (listSize < value) {
                                if (bInsert) {
                                    FUN_008ecd50(removedNodeCount); // Remove node
                                }
                                goto LAB_008efd8c;
                            }
                        }
                        return 0;
                    }

                    // If insertion flag is set, either re-insert or free the old node
                    if (bInsert) {
                        int existingNode = FUN_004059b0(localHash); // Possibly find node by hash
                        if (existingNode == 0) {
                            FUN_008ef6b0(localHash); // Insert new node
                        } else {
                            FUN_006f9af0(existingNode); // Overwrite existing
                        }
                    }
                }
            }
        }
    }

LAB_008efd8c:
    if (!bInsert) {
        return 1;
    }
    // Final retrieval of the just-inserted node
    result = FUN_008ef8a0(value, 0);
    return result;
}