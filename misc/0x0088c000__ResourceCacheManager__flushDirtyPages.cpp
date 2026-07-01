// FUNC_NAME: ResourceCacheManager::flushDirtyPages
void __thiscall ResourceCacheManager::flushDirtyPages(void)
{
    int *pagePtr;
    int pageCount;
    uint pageIdx;
    uint *hashNode;
    int entryBase;
    int entryOffset;
    uint hashValue;
    uint **nodeOrSentinelPtr;
    uint bucketIdx;
    int i;
    uint tableSize;
    undefined4 *bucketArray;
    int *pageArray;
    int remaining;
    uint *foundNode;
    undefined4 *bucketHeadPtr;
    uint *sentinelNode;
    undefined4 *sentinelPtr;
    undefined1 keyBuffer[12];

    // Check if dirty flag is set at +0xae
    if (*(char *)(this + 0xae) != '\0') {
        // Clear dirty flag
        *(undefined1 *)(this + 0xae) = 0;
        // Clear internal counters (likely resets some dirty list)
        clearDirtyFlag(); // FUN_0088b870
        *(undefined4 *)(this + 0x1c0) = 0;
        *(undefined4 *)(this + 0x1d8) = 0;

        pageIdx = 0;
        // Number of pages in the list at +0x78
        if (*(int *)(this + 0x78) != 0) {
            pageArray = (int *)(this + 0x50);
            tableSize = DAT_00e54200; // Global hash table size
            bucketArray = (undefined4 *)PTR_DAT_00e541fc; // Global hash table bucket array

            do {
                pagePtr = *pageArray; // Current page pointer
                // Number of entries in this page (+0x0c)
                remaining = *(int *)(pagePtr + 0xc);
                if (0 < remaining) {
                    entryOffset = 0;
                    do {
                        // Base of entry data (+0x08)
                        entryBase = *(int *)(pagePtr + 8);
                        // Compute hash from first 4 ints of entry (16 bytes)
                        hashValue = ((*(int *)(entryBase + entryOffset) * 0x21 +
                                      *(int *)(entryBase + entryOffset + 4)) * 0x21 +
                                      *(int *)(entryBase + entryOffset + 8)) * 0x21 +
                                      *(int *)(entryBase + entryOffset + 0xc);
                        bucketIdx = hashValue % tableSize;

                        // Search hash bucket linked list
                        for (hashNode = (uint *)bucketArray[bucketIdx];
                             hashNode != (uint *)0x0;
                             hashNode = (uint *)hashNode[7]) // next pointer at +28 (0x1c)
                        {
                            if (hashValue == *hashNode) { // Compare full hash
                                foundNode = hashNode;
                                bucketHeadPtr = bucketArray + bucketIdx;
                                nodeOrSentinelPtr = &foundNode;
                                goto LAB_0088c0c8;
                            }
                        }
                        // Not found: use sentinel (global bucket tail)
                        sentinelNode = (uint *)bucketArray[tableSize];
                        sentinelPtr = bucketArray + tableSize;
                        nodeOrSentinelPtr = &sentinelNode;
LAB_0088c0c8:
                        hashNode = *nodeOrSentinelPtr;
                        // If node is not the sentinel
                        if (hashNode != (uint *)bucketArray[tableSize]) {
                            // Reference count at hashNode[6] (offset +24)
                            if (hashNode[6] == 1) {
                                // Release this cached entry (mark dirty/evict)
                                releaseCachedEntry(keyBuffer, hashNode, nodeOrSentinelPtr[1]);
                                // Re-fetch global table size and bucket array
                                tableSize = DAT_00e54200;
                                bucketArray = (undefined4 *)PTR_DAT_00e541fc;
                                // If resize flag is 0, resize hash table
                                if (DAT_00e54204 == 0) {
                                    freeHashTable(PTR_DAT_00e541fc, DAT_00e54200);
                                    DAT_00e54204 = 0;
                                    if (1 < DAT_00e54200) {
                                        reinitializeHashTable(PTR_DAT_00e541fc);
                                    }
                                    // Reset globals to default single-bucket table
                                    _DAT_00e54208 = _DAT_00d5780c;
                                    _DAT_00e5420c = DAT_00d5eee4;
                                    DAT_00e54200 = 1;
                                    PTR_DAT_00e541fc = (undefined *)&DAT_00ef4398;
                                    DAT_00e54204 = 0;
                                    _DAT_00e54210 = 0;
                                    tableSize = 1;
                                    bucketArray = &DAT_00ef4398;
                                }
                            } else {
                                // Decrement reference count
                                hashNode[6] = hashNode[6] - 1;
                                tableSize = DAT_00e54200;
                                bucketArray = (undefined4 *)PTR_DAT_00e541fc;
                            }
                        }
                        entryOffset += 0x18; // Move to next entry (24 bytes each)
                        remaining--;
                    } while (remaining != 0);
                }
                pageArray++;
                pageIdx++;
            } while (pageIdx < *(uint *)(this + 0x78));
        }
    }
    return;
}