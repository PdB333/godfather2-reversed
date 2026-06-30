// FUNC_NAME: ListNodeDoublyLinkedList::moveNodeToHead
void __thiscall moveNodeToHead(int* this, int parent) {
    int* node = (int*)*this;                          // +0x00: current head node
    *this = *(int*)(node + 2);                       // +0x08: node->next becomes new head

    if (*(char*)(*(int*)(node + 2) + 0x15) == '\0') { // flag at +0x15 in next node
        *(int**)(*(int*)(node + 2) + 1) = this;      // +0x04: update previous pointer of next node to head pointer
    }
    *(int*)(node + 1) = this[1];                     // +0x04: set node->prev to second field of this (old tail?)

    // Now check if this node was the head of a different list (via parent->+0x1c +4)
    if (this == *(int**)(*(int*)(parent + 0x1c) + 1)) { // compare this to parent's head pointer
        *(int*)(*(int*)(parent + 0x1c) + 1) = (int)node; // update parent's head to our node
        *(int**)(node + 2) = this;                      // +0x08: node->next points to this (head pointer)
        this[1] = (int)node;                            // +0x04: second field now points to node
        return;
    }

    // Check if this is the head of the list managed by the second field
    int* secondField = (int*)this[1];
    if (this == (int*)secondField[2]) {                  // +0x08: secondField+8 is pointer to head?
        secondField[2] = (int)node;                      // update that head to node
        *(int**)(node + 2) = this;                       // node->next points to this
        this[1] = (int)node;                             // update second field
        return;
    }

    // General case: insert node before the list pointed by secondField
    *secondField = (int)node;                            // secondField becomes node pointer
    *(int**)(node + 2) = this;                           // node->next points to this (head of list)
    this[1] = (int)node;                                 // second field points to node
}