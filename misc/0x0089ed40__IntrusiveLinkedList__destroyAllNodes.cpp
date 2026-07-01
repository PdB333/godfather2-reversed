// FUNC_NAME: IntrusiveLinkedList::destroyAllNodes

void __thiscall IntrusiveLinkedList::destroyAllNodes(void)
{
    // Node layout: +0x00 next, +0x04 prev, +0x08 data pointer
    Node* sentinel = (Node*)this;                // sentinel node embedded in object
    Node* currentNode = sentinel->next;          // *this -> first real node

    while (currentNode != sentinel)
    {
        Node* nextNode = currentNode->next;      // save next before deletion
        if (currentNode->dataPtr != 0)           // if data handle exists
        {
            destroyData(currentNode->dataPtr);    // clean up the data object
        }
        freeNode(currentNode);                   // deallocate the node
        currentNode = nextNode;
    }
}