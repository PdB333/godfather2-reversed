// FUNC_NAME: ListNode::~ListNode
int __thiscall ListNode::~ListNode(ListNode* this, byte flags) {
    // +0x28: vtable pointer
    // +0x18: previous node pointer (prev)
    // +0x1c: next node pointer (next)
    // +0x20: data pointer or list head pointer (head)
    this->vtable = &g_ListNodeVTable; // PTR_LAB_00e317cc

    // Unlink this node from the doubly linked list
    if (this->prev != nullptr) {
        if (this->next == nullptr) {
            // Only prev exists: set prev's next to the list head
            this->prev->next = this->head; // offset +4 from prev
        } else {
            // Both prev and next exist: set next's prev to the list head
            this->next->prev = this->head; // offset +8 from next
        }
        if (this->head != nullptr) {
            // Set head's next to this node's next
            this->head->next = this->next; // offset +4 from head
        }
    }
    // Call base destructor or cleanup
    FUN_0064d150();
    // If flag indicates deletion, free memory
    if ((flags & 1) != 0) {
        FUN_009c8eb0(this);
    }
    return static_cast<int>(reinterpret_cast<uintptr_t>(this));
}