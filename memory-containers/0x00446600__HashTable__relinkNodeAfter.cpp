// FUNC_NAME: HashTable::relinkNodeAfter
void __thiscall HashTable::relinkNodeAfter(void* thisPtr, void* node, uint32_t key)
{
    // +0x48: bucket_array (pointer to array of bucket heads)
    // +0x4c: bucket_count (modulus for hashing)
    BucketNode** bucketArray = *(BucketNode***)((char*)thisPtr + 0x48);
    uint32_t bucketCount = *(uint32_t*)((char*)thisPtr + 0x4c);
    uint32_t bucketIndex = key % bucketCount;
    BucketNode* current = bucketArray[bucketIndex]; // head of bucket chain

    // Search bucket chain using next pointer at +0x18
    while (current && current->key != key) {
        current = *(BucketNode**)((char*)current + 0x18);
    }
    if (current == nullptr) return; // key not found in hash bucket

    // Node has double-list links at +0x04 (prevLink) and +0x08 (next)
    uint32_t* nodePrev = *(uint32_t**)((char*)node + 4);
    uint32_t* nodeNext = *(uint32_t**)((char*)node + 8);

    // Remove node from its current double-linked list
    if (nodePrev) {
        *(uint32_t**)nodePrev = nodeNext;
    }
    if (nodeNext) {
        *(uint32_t**)(nodeNext + 1) = nodePrev; // nodeNext->prevLink = nodePrev
    }

    // Clear node's old links
    *(uint32_t**)((char*)node + 8) = nullptr;
    *(uint32_t**)((char*)node + 4) = nullptr;

    // Double-list insertion: use current node's link field at +0x04 as insertion point
    uint32_t** currentLink = (uint32_t**)((char*)current + 4);
    void* oldNext = (void*)*currentLink;

    // Node's next = old next after current
    *(void**)((char*)node + 8) = oldNext;
    // Node's prev points to the link field in current
    *(uint32_t***)((char*)node + 4) = currentLink;

    if (oldNext) {
        // Update old next's prevLink to point to node's next field
        *(uint32_t***)((char*)oldNext + 4) = (uint32_t**)((char*)node + 8);
    }

    // Link current to node
    *currentLink = (uint32_t*)node;

    // Store the key in node at +0x1c
    *(uint32_t*)((char*)node + 0x1c) = key;
}