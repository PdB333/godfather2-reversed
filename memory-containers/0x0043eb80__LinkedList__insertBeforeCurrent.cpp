// FUNC_NAME: LinkedList::insertBeforeCurrent
void __fastcall LinkedList::insertBeforeCurrent(void* thisPtr) {
    // +0x18: pointer to current node (Node*)
    Node* currentNode = *(Node**)((char*)thisPtr + 0x18); 

    // Allocate a new node to be inserted before currentNode.
    // The third parameter (in_EAX) is likely an allocation flag or unused.
    Node* newNode = allocateNode(currentNode, currentNode->prev, in_EAX);

    // Synchronization or bookkeeping step (e.g., lock list mutex)
    lockList();

    // Link new node as the new previous node of currentNode
    currentNode->prev = newNode;

    // Update the next pointer of the node that was previously before currentNode
    // newNode->prev points to that old previous node; set its next to newNode
    newNode->prev->next = newNode;
}