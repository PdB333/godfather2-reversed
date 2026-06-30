// FUNC_NAME: Node::setContainer (intrusive linked list node attachment)
// Function at 0x0071d8a0: Sets the node's owner and inserts it at the tail of the owner's linked list (head at offset +0x48).
// param_1 = this (Node with next at +0, prev at +4)
// param_2 = pointer to owner object (or 0 to detach)
int* __thiscall Node::setContainer(int* this, int* ownerPtr) {
    int* listHead;  // pointer to the sentinel node inside the container at offset 0x48
    if (ownerPtr == 0) {
        listHead = 0;
    } else {
        listHead = (int*)(ownerPtr + 0x48);  // container->listHead (a sentinel node)
    }
    // If already attached to a different container or detached, remove from old list and reattach
    if (this[0] != (int)listHead) {
        if (this[0] != 0) {
            FUN_004daf90(this);  // removes this node from its current list
        }
        this[0] = (int)listHead;  // set node->next = address of sentinel? Actually stores sentinel pointer, not the next node; see insertion code.
        if (listHead != 0) {
            // Insert this node at the end of the circular doubly linked list:
            // node->prev = listHead->prev; listHead->prev = node;
            this[1] = listHead[1];          // node->prev = sentinel->prev (old tail)
            listHead[1] = (int)this;        // sentinel->prev = this (new tail)
        }
    }
    return this;
}