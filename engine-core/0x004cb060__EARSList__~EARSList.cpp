// FUNC_NAME: EARSList::~EARSList
void __thiscall EARSList::~EARSList(byte param_2)
{
    // +0x00: vtable pointer (set to base class vtable 0x00e32808)
    // +0x04: head of intrusive linked list (Node*)

    // Set vtable to base class to prevent virtual calls during destruction
    this->vtable = (void*)0x00e32808;

    // Traverse the linked list and clear each node's fields
    Node* current = this->head;
    while (current != nullptr) {
        Node* next = current->next;  // save next node
        // Clear node fields (assuming first field is element pointer, second is next)
        current->element = nullptr;
        current->next = nullptr;
        current = next;
    }

    // If the delete flag is set, deallocate this object
    if (param_2 & 1) {
        operator delete(this);
    }
}