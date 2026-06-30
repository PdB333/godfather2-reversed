// FUNC_NAME: UnknownClass::cleanupAndCloseHandle
void UnknownClass::cleanupAndCloseHandle()
{
    // Set vtable pointer to base class vtable (PTR_LAB_00e434f0)
    this->vtbl = &PTR_LAB_00e434f0;

    // Close a handle stored at offset +0x10 (this[4] = handle)
    CloseHandle(this->handle); // handle stored at +0x10

    // Reset vtable to another base class vtable (PTR_LAB_00e42de4) - likely second inheritance
    this->vtbl = &PTR_LAB_00e42de4;

    // Walk a singly linked list starting at this->head (offset +0x04)
    Node* current = this->head; // +0x04
    while (current != 0)
    {
        Node* next = current->next; // current[2] = next pointer (offset +0x08)
        // Zero out all three fields of the node (12 bytes)
        current->field0 = 0; // +0x00
        current->field1 = 0; // +0x04
        current->next = 0;   // +0x08
        current = next;
    }
}