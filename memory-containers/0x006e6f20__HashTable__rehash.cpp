// FUNC_NAME: HashTable::rehash
void __fastcall HashTable::rehash(int *thisPtr)
{
    uint oldBucketCount = thisPtr[1];
    uint newBucketCount = oldBucketCount * 2 + 1; // Prime-like size (odd)

    // Allocate new bucket array (cleared)
    HashNode **newBuckets = (HashNode **)operatorNew(newBucketCount * sizeof(HashNode *));
    memset(newBuckets, 0, newBucketCount * sizeof(HashNode *));

    // Iterate over old buckets
    for (uint i = 0; i < oldBucketCount; i++)
    {
        HashNode *currNode = *(HashNode **)(thisPtr[0] + i * sizeof(HashNode *));
        while (currNode != nullptr)
        {
            HashNode *nextNode = currNode->next; // Save next before modifying

            // Extract 16-byte key from the key struct (offset +0x10)
            uint32 keyData[4];
            keyData[0] = *(uint32 *)(currNode->key + 0x10);
            keyData[1] = *(uint32 *)(currNode->key + 0x14);
            keyData[2] = *(uint32 *)(currNode->key + 0x18);
            keyData[3] = *(uint32 *)(currNode->key + 0x1c);

            // Hash function setup and compute
            FUN_004d9af0(); // Possibly hash state initialization
            uint hashVal = FUN_004db320(keyData, 0x10); // Hash of 16 bytes

            // Insert node into new bucket list (at head)
            uint bucketIndex = hashVal % newBucketCount;
            currNode->next = newBuckets[bucketIndex];
            newBuckets[bucketIndex] = currNode;

            currNode = nextNode;
        }
    }

    // Free old bucket array and update table
    operatorDelete((void *)thisPtr[0]);
    thisPtr[0] = (int)newBuckets;
    thisPtr[1] = newBucketCount;
}