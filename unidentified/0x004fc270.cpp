// FUN_004fc270: HashTable::insertMissingEntries
bool __thiscall HashTable::insertMissingEntries(HashTable *this, EntryList *list)
{
    int *bucketPtr; // piVar9 (current bucket)
    int bucketCount; // local_10
    int entryIndex; // iVar7
    int *entryPair; // piVar3 (pointer into list's entry array)
    int nodeIndex; // local_c (new node index from pool)
    int iVar1, iVar4, iVar8;
    uint entryCount; // uVar2
    undefined4 key, value; // uVar5

    // Get number of buckets from list's max size? (param_2[1] is probably maxEntries)
    bucketCount = FUN_004f7a90(list->maxEntries, in_EAX);
    list->insertedFlag = 0; // param_2[0] = 0 (false)
    if (bucketCount == 0) {
        return false;
    }
    if (bucketCount > 0) {
        bucketPtr = (int *)((char *)this + 0x1c); // this->buckets (array of ints)
        do {
            // Check if any existing list entry matches this bucket
            if (0 < list->entryCount) { // param_2[0x16]
                entryPair = (int *)list; // param_2
                do {
                    entryPair = entryPair + 2; // skip to next entry pair (each pair is 2 ints)
                    // Compare bucket value with node->bucketPtr (at node offset 0x24)
                    // FS segment base (TLS memory manager)
                    int *base = **(int **)(__readfsdword(0x2c) + 8); // base of node pool
                    int nodeBucketPtr = *(int *)((char *)base + 0x24 + *entryPair);
                    if (*bucketPtr == nodeBucketPtr) {
                        goto NextBucket; // duplicate found, skip this bucket
                    }
                    entryIndex++;
                } while (entryIndex < list->entryCount);
            }
            // No duplicate, and still room in list
            if (list->entryCount < list->maxEntries) { // param_2[0x16] < param_2[1]
                // Allocate a new node from pool (returns index)
                nodeIndex = FUN_00519c80(); // local_c
                if (nodeIndex != 0) {
                    int *poolBase = **(int **)(__readfsdword(0x2c) + 8); // same base
                    int nodeAddr = poolBase + nodeIndex;
                    // Bucket is a pointer to an object with vtable (getKey + 4, getValue + 8)
                    // entryPair currently points to list entry? Actually entryPair is not set here, but used incorrectly? Let's assume bucketPtr still points to current bucket.
                    // Use the bucket object's methods to get key and value
                    key = (**(code **)(*bucketPtr + 4))(); // getKey
                    value = (**(code **)(*bucketPtr + 8))(); // getValue
                    *(int *)(nodeAddr + 0x10) = key;
                    if (key != 0) {
                        *(int *)(nodeAddr + 0x1c) = value;
                    }
                    // Set node's bucket pointer (offset 0x24) to point to the bucket
                    *(int **)(nodeAddr + 0x24) = bucketPtr;
                    // Initialize prev/next pointers (offset 0 and 4)
                    int *prevNext = (int *)(poolBase + 8 + nodeIndex); // ? Actually they set puVar6 = (int *)(poolBase + 8 + nodeIndex) and set both to 0
                    *prevNext = 0;
                    *(prevNext + 1) = 0;
                    // Link node into the table's head list (using this->headPrev and headNext at +0x14 and +0x18)
                    int *nodeLink = (int *)(poolBase + nodeIndex);
                    *nodeLink = *(int *)((char *)this + 0x14); // node->prev = this->headPrev
                    *(nodeLink + 1) = *(int *)((char *)this + 0x18); // node->next = this->headNext
                    if (*(int *)((char *)this + 0x14) != 0) {
                        // Update previous node's next pointer: (prevNode + 4) = nodeIndex? Actually they do:
                        // piVar3 = (int*)(this->headPrev + poolBase + 8) and set *piVar3 = nodeIndex and piVar3[1] = iStack_8
                        // iStack_8 is uninitialized? That's suspicious. Probably a bug in decompiler. We'll keep as placeholder.
                        int *prevNodeLink = (int *)((char *)poolBase + 8 + *(int *)((char *)this + 0x14));
                        *prevNodeLink = nodeIndex;
                        *(prevNodeLink + 1) = iStack_8; // iStack_8 is local variable from stack? likely should be node->next? But decompiler lost it.
                    }
                    // Update head of list
                    *(int *)((char *)this + 0x14) = nodeIndex; // this->headPrev = nodeIndex
                    *(int *)((char *)this + 0x18) = iStack_8; // this->headNext = iStack_8
                    // Increment node's ref count (offset 0x30)
                    int *refCount = (int *)(poolBase + 0x30 + nodeIndex);
                    *refCount = *refCount + 1;
                    // Add new entry to list's entry array (param_2 + 2 + 2*entryCount)
                    entryCount = list->entryCount; // uVar2
                    if (entryCount < 10) { // arbitrary limit? list->maxEntries may be larger
                        list->entryCount = entryCount + 1; // update count
                        list->entries[entryCount * 2] = nodeIndex; // param_2[entryCount*2 + 2]
                        list->entries[entryCount * 2 + 1] = iStack_8; // param_2[entryCount*2 + 3]
                    }
                    list->insertedFlag = 1; // indicate success
                }
            }
NextBucket:
            bucketPtr = bucketPtr + 1; // move to next bucket
            bucketCount--;
        } while (bucketCount != 0);
    }
    return list->insertedFlag != 0; // return true if any insertion happened
}