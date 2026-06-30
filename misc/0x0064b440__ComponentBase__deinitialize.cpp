// FUNC_NAME: ComponentBase::deinitialize
void __thiscall ComponentBase::deinitialize(void)
{
    // Set vtable pointer to first vtable (likely derived class vtable)
    this->vtable = &PTR_LAB_00e42d64;

    // Check if a flag at offset 0x14 is set; if so, free a dynamically allocated buffer at offset 0x0C
    if (this->flagAllocated != '\0') {
        free(this->allocatedBuffer);
    }

    // Set vtable to base class vtable (after derived cleanup)
    this->vtable = &PTR_LAB_00e42de4;

    // Clear linked list starting at offset 0x04 (listHead)
    ComponentNode* node = this->listHead;
    while (node != nullptr) {
        ComponentNode* next = node->next;
        node->prev = nullptr;
        node->data = nullptr;
        node->next = nullptr;
        node = next;
    }
}