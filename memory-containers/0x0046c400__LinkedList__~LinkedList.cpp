// FUNC_NAME: LinkedList::~LinkedList
LinkedList::~LinkedList(byte deletingFlag) {
    // Set vtable pointer (for safety, e.g. if called from base destructor)
    this->vtable = &vtableTable; // 0x00e32808

    // Traverse and clear linked list (head at +0x04)
    Node* current = this->head;
    while (current != nullptr) {
        Node* next = current->next; // Node layout: +0x00 data, +0x04 next
        current->data = nullptr;
        current->next = nullptr;
        current = next;
    }

    // If called from operator delete (deleting destructor), free memory
    if (deletingFlag) {
        // FUN_009c8eb0 is likely operator delete(void*)
        operator delete(this);
    }
}