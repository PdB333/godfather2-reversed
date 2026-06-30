// FUNC_NAME: NodePool::clearAll
void NodePool::clearAll(void)
{
    int bucketIndex;
    Node *currentNode;
    Node *nextNode;
    int bucketCount;
    unsigned int i;

    i = 0;
    if (this->numBuckets != 0) {
        do {
            currentNode = *(Node **)(this->bucketArray + i * 4);
            if (currentNode != (Node *)0x0) {
                do {
                    nextNode = *(Node **)((int)currentNode + 8);  // +0x8: next pointer in pooled node
                    *(Node **)((int)currentNode + 8) = this->freeList;  // move node to free list
                    this->usedCount = this->usedCount + -1;              // decrement used count
                    this->freeList = currentNode;                        // update free list head
                    currentNode = nextNode;
                } while (nextNode != (Node *)0x0);
                *(int *)(this->bucketArray + i * 4) = 0;  // clear bucket head
            }
            i = i + 1;
        } while (i < (unsigned int)this->numBuckets);
    }
    // free all nodes in the 'toDelete' linked list (each node has next at +0x0)
    Node *deleteNode = (Node *)this->toDeleteList;  // +0x10
    while (deleteNode != (Node *)0x0) {
        Node *nextDelete = (Node *)*deleteNode;  // +0x0: next pointer
        operatorDelete(deleteNode);  // free the allocated block
        deleteNode = nextDelete;
    }
    this->toDeleteList = (Node *)0x0;  // +0x10
    this->freeList = (Node *)0x0;      // +0x08
    return;
}