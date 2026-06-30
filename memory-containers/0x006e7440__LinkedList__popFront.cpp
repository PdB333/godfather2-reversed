// FUNC_NAME: LinkedList::popFront
void __thiscall LinkedList::popFront() {
    Node* node = this->head; // this+0x8
    if (node == nullptr) {
        FUN_006e73f0(); // Allocate or create a new node (lazy)
        node = this->head;
    }
    // Remove the head node from the list
    this->head = node->next; // node+0x4
    node->next = nullptr;    // node+0x4 = 0
    this->size++;            // this+0xC
}