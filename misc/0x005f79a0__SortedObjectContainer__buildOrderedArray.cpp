// FUNC_NAME: SortedObjectContainer::buildOrderedArray
// Reconstructed from Ghidra decompilation at address 0x005f79a0
// Role: Flattens a hash-sorted linked list into a flat array, or returns a pre-sorted array if already sorted.
// The container object has:
// +0x34: pointer to head of linked list of nodes (each node has next at +0x00, key at +0x0B)
// +0x38: flags (bit 3 = sorted flag)
// +0x24: pointer to hash table bucket array (each bucket is 3 words: [sortedListHead, next?, base?])

#include <cstring> // for memset

// Forward declarations of helper functions
void clearNode(int *node);                                      // FUN_004daf90
void storeSortedArray(int param, void *array);                  // FUN_005f7e50
void clearBucket(int *bucket);                                  // FUN_005f7ba0

void *SortedObjectContainer::buildOrderedArray(
    MemoryManager *allocator,                                   // param_1
    SortedObjectContainer *container,                           // param_2
    int *outCount)                                             // param_3
{
    int *headNode;           // piVar7
    byte flags;              // bVar1
    int nodeCount;           // iVar6
    void *array;             // _Dst
    int i;                   // loop index
    bool breakFlag;          // bVar3
    int *currentSlot;        // piVar4 (points into array)
    int *hashTableBase;      // derived from container->hashTable
    int sortedListHead;      // iVar2
    int *bucketEntry;        // piVar5
    int tempHead;            // iStack_20
    int savedNext;           // iStack_1c
    int insertionValue;      // iStack_18
    int dummy[3] = {0};      // local_c, local_8, local_4

    // Get the head node and flags from the container
    headNode = *(int **)(container + 0x34);
    flags = *(byte *)(container + 0x38);
    *outCount = 0;

    if ((flags & 8) == 0) {
        // Not sorted: count nodes in the linked list
        if (headNode != nullptr) {
            nodeCount = 0;
            int *node = headNode;
            do {
                node = (int *)*node;  // follow next pointer
                nodeCount++;
            } while (node != nullptr);
            *outCount = nodeCount;
        }
    } else {
        // Already sorted: return 2 (placeholder? or fixed count)
        *outCount = 2;
    }

    nodeCount = *outCount;

    // Allocate array via the allocator's virtual function at +0x10
    // Each element is 3 words (12 bytes)
    array = allocator->allocate(nodeCount * 12, &dummy);
    memset(array, 0, nodeCount * 12);

    if (array == nullptr) {
        return nullptr;
    }

    if ((*(byte *)(container + 0x38) & 8) == 0) {
        // Not sorted: traverse list and insert nodes into array with ordering
        i = *outCount - 1;
        breakFlag = false;
        currentSlot = (int *)array + i * 3;  // point to last element

        do {
            if (i < 0) {
                if (!breakFlag) {
                    return array;
                }
                break;
            }

            // Get bucket entry from hash table (key at node+0x0B)
            hashTableBase = *(int *)(container + 0x24);
            bucketEntry = (int *)(hashTableBase + (unsigned char)*(byte *)((int)headNode + 0x0B) * 3 * 4);
            sortedListHead = *bucketEntry;

            if (sortedListHead == 0) {
                // No existing list for this bucket, signal break
                breakFlag = true;
            } else {
                // Compute insertion value: offset from bucket base * 0x24? 
                insertionValue = *(int *)(sortedListHead + 0x20) + 
                    (((int)headNode - bucketEntry[2]) / 12) * 0x24;
                savedNext = *(int *)(sortedListHead + 4);

                // Use a temporary head to manipulate linked list insertion
                tempHead = sortedListHead;
                if ((currentSlot != &tempHead) && (*currentSlot != sortedListHead)) {
                    if (*currentSlot != 0) {
                        clearNode(currentSlot);
                    }
                    *currentSlot = sortedListHead;
                    if (sortedListHead != 0) {
                        currentSlot[1] = *(int *)(sortedListHead + 4);
                        *(int **)(sortedListHead + 4) = currentSlot;
                    }
                }
                currentSlot[2] = insertionValue;

                // Restore previous list head
                if (tempHead != 0) {
                    int *prev = *(int **)(tempHead + 4);
                    if (prev == &tempHead) {
                        *(int *)(tempHead + 4) = savedNext;
                        headNode = (int *)*headNode;
                        goto nextIter;
                    }
                    while ((int *)prev[1] != &tempHead) {
                        prev = (int *)prev[1];
                    }
                    prev[1] = savedNext;
                }
                headNode = (int *)*headNode;
            }

nextIter:
            i--;
            currentSlot -= 3;
        } while (!breakFlag);

        // After processing, store the array via callback and return null
        storeSortedArray(dummy[0], array);
        return nullptr;
    } else {
        // Already sorted: clear two buckets? (container+8 and container+0x14)
        clearBucket(container + 8);
        clearBucket(container + 0x14);
        return array;
    }
}