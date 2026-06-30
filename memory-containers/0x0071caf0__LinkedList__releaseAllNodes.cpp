// FUNC_NAME: LinkedList::releaseAllNodes
void __thiscall LinkedList::releaseAllNodes(NodeList* this) {
    Node* currentNode = this->head; // +0x00
    while (currentNode != 0) {
        Node* nextNode = *(int*)(currentNode + 4); // node->next at +0x04
        // Call destructor on the node via the list's node destructor vtable
        this->nodeDestructor->vtable[1](currentNode, 0); // +0x10 for node destructor ptr, vtable idx 1
        currentNode = nextNode;
        this->head = currentNode;
    }
    this->tail = 0;  // +0x04
    this->head = 0;  // +0x00
    this->count = 0; // +0x08
}