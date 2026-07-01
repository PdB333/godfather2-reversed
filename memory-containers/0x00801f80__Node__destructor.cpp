// FUNC_NAME: Node::destructor
int __thiscall Node::destructor(Node *this, byte shouldDelete) {
    // Set vtable pointer to the class's vtable (0x00e317cc)
    *(void ***)(this + 0x28) = &PTR_LAB_00e317cc;

    // If this->prev (offset +0x18) is not null, adjust linked list pointers
    if (*(int *)(this + 0x18) != 0) {
        if (*(int *)(this + 0x1c) == 0) {
            // No next node: set prev->next = this->next (offset +0x20)
            *(int *)(*(int *)(this + 0x18) + 4) = *(int *)(this + 0x20);
        } else {
            // Has next: set next->prev = this->next
            *(int *)(*(int *)(this + 0x1c) + 8) = *(int *)(this + 0x20);
        }
        // If this->next (offset +0x20) exists, set its prev = this->prev
        if (*(int *)(this + 0x20) != 0) {
            *(int *)(*(int *)(this + 0x20) + 4) = *(int *)(this + 0x1c);
        }
    }

    // Call base/embedded object destructor
    FUN_0064d150();

    // If shouldDelete is true, free memory (operator delete or custom dealloc)
    if ((shouldDelete & 1) != 0) {
        FUN_009c8eb0(this);
    }

    return (int)this;
}