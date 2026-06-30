//FUNC_NAME: ResourceList::~ResourceList
void __fastcall ResourceList::~ResourceList(ResourceList* this)
{
    // Set vtable to derived class (current class)
    this->vtable = &PTR_FUN_00e407c8;

    // Free the managed resource if present (offset +0x8)
    if (this->resourcePtr != nullptr) {
        FUN_005f7e50(DAT_01223520, this->resourcePtr); // deallocate via global allocator
    }

    // Switch vtable to base class (for proper virtual dispatch during base cleanup)
    this->vtable = &PTR_FUN_00e32808;

    // Clear the linked list at offset +0x4
    ListNode* currentNode = this->listHead;
    while (currentNode != nullptr) {
        ListNode* nextNode = currentNode->next; // +0x4
        currentNode->next = nullptr;            // clear next pointer
        currentNode->data = nullptr;            // clear data pointer (+0x0)
        currentNode = nextNode;
    }
    // Note: nodes themselves are not freed; they may be embedded or managed externally
}