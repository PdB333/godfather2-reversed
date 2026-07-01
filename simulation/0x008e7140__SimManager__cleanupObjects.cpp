// FUNC_NAME: SimManager::cleanupObjects
void __fastcall SimManager::cleanupObjects(SimManager* this)
{
    SimManager::Node* current;
    SimManager::Node* next;

    // Set vtable to base class (offset 0x00)
    this->vtable = &PTR_FUN_00d80590;              // +0x00: vtable pointer 1
    this->vtable2 = &PTR_LAB_00d8059c;             // +0x08: vtable pointer 2 (offset 2)
    this->vtable3 = &PTR_LAB_00d80580;             // +0x44: vtable pointer 3 (offset 0x11)
    this->vtable4 = &PTR_LAB_00d8057c;             // +0x50: vtable pointer 4 (offset 0x14)

    // Call base class initialization/cleanup (likely destructor or constructor)
    FUN_0046c640();

    // Override first vtable to derived class
    this->vtable = &PTR_FUN_00e32808;              // +0x00: vtable pointer overridden

    // Walk linked list starting at +0x04 (list head) and zero out each node
    current = this->listHead;                       // +0x04: linked list head
    while (current != nullptr) {
        next = current->next;                       // +0x04: [node+0x04] next pointer
        current->next = nullptr;                    // +0x04: zero next
        current->data = nullptr;                    // +0x00: zero data pointer
        current = next;
    }
}