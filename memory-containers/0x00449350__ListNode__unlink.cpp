// FUNC_NAME: ListNode::unlink
// Removes this node from a doubly linked list.
// Returns the previous and next pointers via output parameters,
// but only sets the one that becomes the new head/tail.
// Specifically: if this was the first node, sets outNext to the new head;
// if this was the last node, sets outPrev to the new tail.

struct ListNode {
    ListNode* next; // +0x00
    ListNode* prev; // +0x04
};

void __thiscall ListNode::unlink(ListNode** outNext, ListNode** outPrev) {
    if (this->prev == nullptr) {
        *outNext = this->next;
        if (this->next != nullptr) {
            this->next->prev = nullptr;
        }
    }
    else {
        this->prev->next = this->next;
    }

    if (this->next != nullptr) {
        this->next->prev = this->prev;
        this->next = nullptr;
        this->prev = nullptr;
        return;
    }

    // Node was the tail
    *outPrev = this->prev;
    if (this->prev != nullptr) {
        this->prev->next = nullptr;
    }
    this->next = nullptr;
    this->prev = nullptr;
}