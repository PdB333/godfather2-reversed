// FUNC_NAME: HashTable::rehash

void HashTable::rehash(void)
{
    uint newBucketCount;
    Node *currentNode;
    Node *nextNode;
    int *keyPointer;
    uint hashValue;
    uint oldBucketIndex;
    Node **newBuckets;

    newBucketCount = bucketCount * 2 + 1;
    // Allocate new bucket array (size: newBucketCount pointers)
    newBuckets = (Node **)operator new[](newBucketCount * sizeof(Node *));
    _memset(newBuckets, 0, newBucketCount * sizeof(Node *));

    oldBucketIndex = 0;
    if (bucketCount != 0) {
        do {
            // Traverse the linked list in each old bucket
            currentNode = buckets[oldBucketIndex];
            while (currentNode != nullptr) {
                // Save next node before modifying
                nextNode = currentNode->next;

                // Determine how to get the key pointer based on node type
                if ((currentNode->flags & 1) == 0) {
                    // Normal node: walk through a chain of key fragments
                    keyPointer = &currentNode->keyStart; // offset +0x20
                    int *walkPtr = &currentNode->keyField2; // offset +0x24
                    while (*walkPtr != 0x40000000) {
                        keyPointer = (int *)((int)keyPointer + *keyPointer);
                        walkPtr = keyPointer + 1;
                    }
                    keyPointer = keyPointer + 2; // points to actual key
                }
                else if (currentNode->keyField2 == 0) {
                    // Special empty-key node (global sentinel)
                    if ((s_emptyKeyUsed & 1) == 0) {
                        s_emptyKeyUsed |= 1;
                        s_emptyKey1 = 0;
                        s_emptyKey2 = 0;
                        s_emptyKey3 = 0;
                        s_emptyKey4 = 0;
                    }
                    keyPointer = &s_emptyKey1;
                }
                else {
                    // Inline key at offset +0x24 relative to node base
                    keyPointer = (int *)(currentNode->keyField2 + 0x24 + (int)currentNode);
                }

                // Compute hash and reinsert into new bucket
                hashValue = computeHash(keyPointer);
                currentNode->next = newBuckets[hashValue % newBucketCount];
                newBuckets[hashValue % newBucketCount] = currentNode;

                currentNode = nextNode;
            }
            oldBucketIndex = oldBucketIndex + 1;
        } while (oldBucketIndex < (uint)bucketCount);
    }

    // Free old bucket array
    operator delete[](buckets);
    buckets = newBuckets;
    bucketCount = newBucketCount;
}