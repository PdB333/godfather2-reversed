// FUNC_NAME: HashTable::removeNode
// Reconstructed hash table removal with free list reclamation
// Struct fields: +0x04 numBuckets, +0x08 bucketArray (pointers to chains), +0x0C freeListHead, +0x10 usedCount
uint __fastcall HashTable::removeNode(HashTable* this, uint key)
{
    uint* bucketPtr;   // Pointer to bucket head pointer in the bucket array
    uint* currentNode; // Current node being examined
    uint* prevNode;    // Previous node in the chain
    uint bucketIndex;  // Calculated bucket index

    // Calculate bucket index from key and number of buckets
    bucketIndex = key % this->numBuckets;
    bucketPtr = &((uint*)this->buckets)[bucketIndex]; // Equivalent to (uint*)((char*)this + 8) + bucketIndex*4
    currentNode = (uint*)*bucketPtr;
    prevNode = nullptr;

    // Walk the chain to find the node with matching key
    while (currentNode != nullptr) {
        if (*currentNode == key) {
            break; // Found
        }
        prevNode = currentNode;
        currentNode = (uint*)currentNode[2]; // Next node pointer at offset 8 in node structure
    }

    if (currentNode == nullptr) {
        // Key not found in the table
        return 1;
    }

    // Remove node from its chain
    if (prevNode != nullptr) {
        // Not the first node in the chain; update previous node's next
        prevNode[2] = (uint)currentNode[2];
    } else {
        // First node in the chain; update bucket head
        *bucketPtr = (uint)currentNode[2];
    }

    // Add the removed node to the free list (head at offset 0x0C)
    // The node's next pointer becomes the old free list head
    currentNode[2] = this->freeListHead;
    this->freeListHead = (uint)currentNode;

    // Decrement the count of active (used) nodes
    this->usedCount--;

    return 0; // Success
}