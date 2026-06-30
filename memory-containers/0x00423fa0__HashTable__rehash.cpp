// FUNC_NAME: HashTable::rehash
// Address: 0x00423fa0
// Rehashes the hash table to a new size (oldSize * 2 + 1). Used for hash table resizing in EA EARS engine.

__thiscall void HashTable::rehash(int* thisPtr)
{
    // thisPtr: pointer to HashTable structure
    // offset +0: bucket array pointer
    // offset +4: number of buckets

    uint oldNumBuckets = thisPtr[1];
    uint newNumBuckets = oldNumBuckets * 2 + 1; // New bucket count (odd number)
    uint newBucketArraySize = newNumBuckets * 4;

    // Allocate memory for new bucket array (FUN_009c8e80 is a memory allocator)
    void* newBucketArray = operator new(newBucketArraySize);
    memset(newBucketArray, 0, newBucketArraySize);

    // Iterate over old buckets
    uint bucketIndex = 0;
    if (oldNumBuckets != 0) {
        do {
            HashTableNode** oldBucketArray = (HashTableNode**)thisPtr[0];
            HashTableNode* node = oldBucketArray[bucketIndex];
            while (node != nullptr) {
                HashTableNode* nextNode = node->next; // node[2] is next pointer
                uint newBucket = node->hash % newNumBuckets;
                node->next = ((HashTableNode**)newBucketArray)[newBucket];
                ((HashTableNode**)newBucketArray)[newBucket] = node;
                node = nextNode;
            }
            bucketIndex++;
        } while (bucketIndex < oldNumBuckets);
    }

    // Free old bucket array (FUN_009c8f10 is memory deallocation)
    operator delete((void*)thisPtr[0]);

    // Update table structure
    thisPtr[0] = (int)newBucketArray;
    thisPtr[1] = newNumBuckets;
}