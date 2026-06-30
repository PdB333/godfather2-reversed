// FUNC_NAME: DoubleLinkedList::moveToFront
void __thiscall DoubleLinkedList::moveToFront(int this, int** headPtr) {
    int* pNode = *headPtr;                 // Get current front node
    *headPtr = *(int**)(pNode + 8);        // Remove node from list: head = node->next

    if (*(char*)(*(int*)(pNode + 8) + 0x29) == '\0') {
        *(int**)(*(int*)(pNode + 8) + 4) = (int*)headPtr;  // If new head not a sentinel, set its prev to headPtr
    }

    *(int*)(pNode + 4) = (int)headPtr[1];   // Set node->prev to the tail stored in headPtr[1]

    // Check if headPtr is also the tail pointer (i.e., list had only one node)
    if (headPtr == *(int***)(*(int*)(this + 4) + 4)) {
        *(int*)(*(int*)(this + 4) + 4) = (int)pNode;   // Update tail to node
        *(int**)(pNode + 8) = (int*)headPtr;           // node->next = headPtr
        headPtr[1] = (int)pNode;                       // headPtr[1] = node
        return;
    }

    int** prevNode = (int**)headPtr[1];     // Get the previous node (from tail pointer)
    if (headPtr == (int**)prevNode[2]) {    // If headPtr matches the previous node's "head" field
        prevNode[2] = (int)pNode;           // Update previous node's "head" field
        *(int**)(pNode + 8) = (int*)headPtr; // node->next = headPtr
        headPtr[1] = (int)pNode;            // headPtr[1] = node
        return;
    }

    *prevNode = (int)pNode;                 // Update prevNode[0] to node
    *(int**)(pNode + 8) = (int*)headPtr;    // node->next = headPtr
    headPtr[1] = (int)pNode;                // headPtr[1] = node
}