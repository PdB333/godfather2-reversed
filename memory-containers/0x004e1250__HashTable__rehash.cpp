// FUNC_NAME: HashTable::rehash
void __thiscall HashTable::rehash(int* thisPtr)
{
    // thisPtr[0] = pointer to bucket array (array of linked list heads)
    // thisPtr[1] = number of buckets (capacity)
    uint32_t oldBucketCount = thisPtr[1];
    uint32_t newBucketCount = oldBucketCount * 2 + 1;

    // Allocate new bucket array (size = newBucketCount * 4 bytes)
    void* newBuckets = operator new(newBucketCount * 4);  // using custom allocator? placeholder
    memset(newBuckets, 0, newBucketCount * 4);

    // Iterate over each old bucket
    for (uint32_t oldIdx = 0; oldIdx < oldBucketCount; ++oldIdx)
    {
        HashNode* node = *(HashNode**)(thisPtr[0] + oldIdx * 4);  // old bucket pointer
        while (node != nullptr)
        {
            // node layout: +0 key pointer, +4 value, +8 next pointer
            uint8_t* keyData = (uint8_t*)node->key;
            HashNode* nextNode = node->next;  // save before reinserting

            // Hash the first 16 bytes of the key
            uint32_t hash = 0;
            if (keyData != nullptr)
            {
                uint8_t* end = keyData + 16;
                for (; keyData < end; ++keyData)
                {
                    hash = hash * 0x1003f + *keyData;
                }
            }

            // Insert node into new bucket chain (head insertion)
            uint32_t newIdx = hash % newBucketCount;
            node->next = *(HashNode**)((int)newBuckets + newIdx * 4);
            *(HashNode**)((int)newBuckets + newIdx * 4) = node;

            node = nextNode;
        }
    }

    // Free old bucket array
    operator delete((void*)thisPtr[0]);  // placeholder deallocation

    // Update structure
    thisPtr[0] = (int)newBuckets;
    thisPtr[1] = newBucketCount;
}