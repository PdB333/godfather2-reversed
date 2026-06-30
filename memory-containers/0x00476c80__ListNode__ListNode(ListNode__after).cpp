// FUNC_NAME: ListNode::ListNode(ListNode* after)
void __fastcall ListNode::ListNode(ListNode* after) {
    // Initalize virtual function table (offset 0x00)
    this->vtable = &ListNode::vtable; // PTR_FUN_00e31e2c

    // Insert this node into a doubly-linked intrusive list after 'after'
    // The list hook is at offset 0x04 (next) and 0x08 (prev).
    // Actually, the pointer arithmetic suggests the list stores pointers to the hook fields,
    // not to the nodes themselves.

    ListNode* nextNode = after->next; // offset 0x04
    this->next = nextNode;            // offset 0x04
    this->prev = nullptr;            // offset 0x08, initially null

    if (nextNode != nullptr) {
        // Set our prev to the prev of the node that will be after us.
        // This copies the previous node's link pointer.
        this->prev = nextNode->prev; // offset 0x08 from nextNode
        // Update the new 'after' node's prev pointer to point to our own next field.
        // This is an intrusive list where the hook itself is what gets linked.
        nextNode->prev = &(this->next); // offset 0x04 of this (address of this->next)
    }
    // Note: The original 'after' node's next pointer is NOT updated here.
    // It is presumably set by the caller (e.g., by making this a constructor of a sentinel head).
}