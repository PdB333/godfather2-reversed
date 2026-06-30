// FUNC_NAME: HashTable::insert
void __thiscall HashTable::insert(HashTable *this, HashBucket *bucket) {
    int nodeCount = this->nodeCount;
    int nodeCapacity = this->nodeCapacity;

    if (nodeCount == nodeCapacity) {
        // Double capacity (or start at 1 if empty)
        int newCapacity = (nodeCapacity == 0) ? 1 : nodeCapacity * 2;
        growBuffer(newCapacity); // FUN_0074c870 - reallocate node buffer
    }

    // Get pointer to next free node slot in the linear buffer
    Node *newNode = (Node *)(this->nodeBuffer + nodeCount * sizeof(Node)); // sizeof(Node) = 8
    this->nodeCount++;

    // Store the bucket pointer (or some identifier) in the node
    // bucket->unk is placed in the first field of the node
    int bucketUnk = bucket->unk;
    newNode->unk = bucketUnk;
    newNode->next = nullptr;

    if (bucketUnk != 0) {
        // Insert into the intrusive linked list anchored at (bucketUnk + 4)
        // The bucket's next pointer is actually stored at the address bucketUnk + 4
        int **headPtr = (int **)(bucketUnk + 4);
        newNode->next = *headPtr;   // old head becomes newNode's next
        *headPtr = newNode;         // newNode becomes new head
    }
}