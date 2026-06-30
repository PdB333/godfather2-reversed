// FUNC_NAME: ListNode::insertAfter

class ListNode {
public:
    ListNode* prev;  // +0x00: pointer to previous node in the list (or null)
    ListNode* next;  // +0x04: pointer to next node in the list (or null)

    // Removes this node from its current list (implemented elsewhere)
    void remove();  // calls FUN_004daf90 (likely unlink from list)
};

// Inserts this node after the list node located at offset 0x48 within the given container.
// @param container: pointer to an object that contains a ListNode at offset 0x48 (the anchor node)
// @return this node
ListNode* __thiscall ListNode::insertAfter(void* container) {
    ListNode* anchor = nullptr;
    if (container != nullptr) {
        anchor = reinterpret_cast<ListNode*>(static_cast<char*>(container) + 0x48);
    }
    // No change if anchor is null (anchor remains zero)

    if (prev != anchor) {
        if (prev != nullptr) {
            remove(); // detach from current list
        }
        prev = anchor;
        if (anchor != nullptr) {
            next = anchor->next;
            anchor->next = this;
        }
    }
    return this;
}