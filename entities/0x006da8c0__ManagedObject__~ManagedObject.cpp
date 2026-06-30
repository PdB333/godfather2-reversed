// FUNC_NAME: ManagedObject::~ManagedObject
void __fastcall ManagedObject::~ManagedObject(ManagedObject* this) {
    // Set vtable to destructor-only vtable (to prevent further virtual calls)
    this->vtable = &VTABLE_D1;
    if (this->field_0xE8 != 0) {
        deallocate(this->field_0xE8);
        this->field_0xE8 = 0;
    }
    if (this->field_0xE0 != 0) {
        deallocate(this->field_0xE0);
        this->field_0xE0 = 0;
    }
    // Set vtable to post-destruction vtable (for safety after destruction)
    this->vtable = &VTABLE_D2;
    // Clear linked list starting at offset +0x4
    ListNode* current = this->listHead;
    while (current != 0) {
        ListNode* next = current->next;
        current->next = 0;
        current->data = 0;
        current = next;
    }
}