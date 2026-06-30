// FUNC_NAME: HashTable::rehash
void HashTable::rehash()
{
    uint newBucketCount = bucketCount * 2 + 1; // new count = old*2+1
    void* newBuckets = allocateMemory(newBucketCount * 4); // allocate array of pointers
    memset(newBuckets, 0, newBucketCount * 4);

    uint bucketIndex = 0;
    if (bucketCount != 0)
    {
        do
        {
            int node = bucketArray[bucketIndex]; // first node in this bucket chain
            while (node != 0)
            {
                int next = *(int*)(node + 0x30); // save next pointer before rehashing
                uint hash = hashValue(node + 0x20); // hash the key at offset +0x20
                // insert at head of new bucket
                *(int*)(node + 0x30) = ((int*)newBuckets)[hash % newBucketCount];
                ((int*)newBuckets)[hash % newBucketCount] = node;
                node = next;
            }
            bucketIndex++;
        } while (bucketIndex < (uint)bucketCount);
    }

    freeMemory(bucketArray); // free old bucket array
    bucketArray = (int*)newBuckets;
    bucketCount = newBucketCount;
}