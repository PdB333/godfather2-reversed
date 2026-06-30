// FUN_NAME: ObjectManager::destroyAllByTypeID
void ObjectManager::destroyAllByTypeID(int objectTypeId)
{
    uint *hashBucket;
    uint *node;
    int *linkedNode;
    int *freeNode;
    int *nextNode;
    uint uVar;
    // +0x48: hash table pointer
    // +0x4c: hash table size
    hashBucket = *(uint **)(*(int *)(this + 0x48) + (objectTypeId % *(uint *)(this + 0x4c)) * 4);

    do {
        if (hashBucket == (uint *)0x0) {
            // Fall through to scanning the quad-list arrays (active lists)
            goto scan_quad_lists;
        }

        if (*hashBucket == objectTypeId) {
            // Found a match in the hash table bucket
            if (hashBucket != (uint *)0x0 && hashBucket != (uint *)0xfffffffc) {
                // Process callback chain (vtable at +0xc)
                linkedNode = (int *)hashBucket[4];
                while (linkedNode != (int *)0x0) {
                    (**(code **)(*linkedNode + 0xc))();  // Callback vfunc
                    freeNode = linkedNode;
                    if (((linkedNode[5] & 0x8000000U) != 0) &&
                        (freeNode = linkedNode + 0xf, (*(byte *)(linkedNode + 0x10) & 2) != 0)) {
                        // Handle special flag with a stack-based temporary
                        uStack_c = DAT_012067dc;
                        uStack_4 = 0;
                        piStack_8 = freeNode;
                        (**(code **)(*freeNode + 4))(&uStack_c);  // Another vfunc
                    }
                    (**(code **)*freeNode)(1);  // Delete/dispose
                    linkedNode = (int *)hashBucket[4];
                }

                // Process child/resource linked list at node+5 (offset 20 bytes)
                uint *childList = hashBucket + 5;
                uint childHead = *childList;
                while (childHead != 0) {
                    uint *childNode = (uint *)*childList;
                    uint *prevChild = 0;
                    if (childNode != (uint *)0x0) {
                        if ((uint *)childNode[1] != (uint *)0x0) {
                            *(uint *)childNode[1] = childList;  // Unlink previous
                        }
                        *childList = *(uint *)(*childList + 4);  // Set next
                        *childNode = 0;
                        childNode[1] = 0;
                        prevChild = childNode;
                    }

                    // Now move the child to the object free list at +0x68
                    int *freeListNode = (int *)(prevChild + 5);
                    if (prevChild[5] != 0) {
                        int *freeList = (int *)(this + 0x68);  // +0x68: free list head
                        do {
                            int *current = *freeListNode;
                            int temp = 0;
                            if (current != 0) {
                                if (*(int *)(current + 0x10) != 0) {
                                    *(int **)(*(int *)(current + 0x10) + 0xc) = freeListNode;
                                }
                                *freeListNode = *(int *)(*freeListNode + 0x10);
                                *(undefined4 *)(current + 0xc) = 0;
                                *(undefined4 *)(current + 0x10) = 0;
                                temp = current;
                            }
                            *(int *)(temp + 0x10) = *freeList;
                            *(int **)(temp + 0xc) = freeList;
                            if (*freeList != 0) {
                                *(int **)(*freeList + 0xc) = (int *)(temp + 0x10);
                            }
                            *freeList = temp;
                        } while (*freeListNode != 0);
                    }

                    // Remove from hash table (may also free the node)
                    FUN_004483c0(this, objectTypeId);
                    childHead = *childList;
                }

                // Global cleanup functions
                FUN_004492b0();
                FUN_00448630();
            }

            goto scan_quad_lists;
        }

        hashBucket = (uint *)hashBucket[6];  // Next bucket in chain
    } while (true);

scan_quad_lists:
    // Scan the 4 special linked lists (priority levels?) at +0x90..+0x9c
    uVar = 0;
    do {
        int *listHead = *(int **)(this + 0x90 + uVar * 8);  // +0x90: listHead[0..3]
        while (nextNode = listHead, nextNode != (int *)0x0) {
            listHead = (int *)*nextNode;
            if (nextNode[0xb] == objectTypeId) {
                if ((undefined4 *)nextNode[1] == (undefined4 *)0x0) {
                    // Node is head of list
                    *(int **)(this + 0x90 + uVar * 8) = listHead;
                    if (listHead != (int *)0x0) {
                        listHead[1] = 0;
                        goto unlink_and_set_flag;
                    }
                } else {
                    // Node is not head: update previous node's next
                    *(undefined4 *)nextNode[1] = listHead;
                    unlink_and_set_flag:
                    if (*nextNode == 0) {
                        // Node is tail
                        *(undefined4 **)(this + 0x94 + uVar * 8) = (undefined4 *)nextNode[1];  // +0x94: listTail[0..3]
                        if ((undefined4 *)nextNode[1] != (undefined4 *)0x0) {
                            *(undefined4 *)nextNode[1] = 0;
                        }
                    } else {
                        *(int *)(*nextNode + 4) = nextNode[1];  // Update next's prev pointer
                    }
                }

                // Zero out the node's links
                nextNode[1] = 0;
                *nextNode = 0;

                // If this is the first list (uVar==0) and has a specific flag, decrement global counter
                if ((uVar == 0) && ((*(byte *)(nextNode + 5) & 0x20) != 0)) {
                    *(int *)(DAT_0122337c + 0x9c) = *(int *)(DAT_0122337c + 0x9c) + -1;
                    nextNode[5] = nextNode[5] & 0xffffffdf;  // Clear flag
                }
            }
        }
        uVar = uVar + 1;
        if (3 < uVar) {
            return;
        }
    } while (true);
}