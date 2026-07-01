// FUNC_NAME: ListNode::copyFromAndLink
void __thiscall ListNode::copyFromAndLink(ListNode* this, ListNode* source) {
    // Set vtable to base class vtable (first assignment)
    this->vtable = (void**)&PTR_FUN_00e32808;
    // Copy field at offset +0x04 (likely a pointer or ID)
    this->field_04 = source->field_04;
    // Override vtable with derived class vtable
    this->vtable = (void**)&PTR_FUN_00d62bd8;
    // Get the next pointer from source at offset +0x08
    ListNode* nextNode = source->field_08;
    this->field_08 = nextNode;  // this->next = source->next
    this->field_0C = 0;         // initialize prev pointer to null
    if (nextNode != 0) {
        // Insert this node after source in the linked list
        this->field_0C = nextNode->field_04;  // this->prev = nextNode->next
        nextNode->field_04 = &this->field_08; // nextNode->next = &this->next
    }
    // Copy 4-byte value at offset +0x10 (e.g., RGBA color) byte by byte
    this->color[0] = source->color[0];
    this->color[1] = source->color[1];
    this->color[2] = source->color[2];
    this->color[3] = source->color[3];
    // Copy remaining fields
    this->field_14 = source->field_14; // +0x14
    this->field_18 = source->field_18; // +0x18
    this->field_1C = source->field_1C; // +0x1C
    this->field_20 = source->field_20; // +0x20
}