// FUNC_NAME: ListNode::attachToList
// Function at 0x006e61a0.
// Attaches this node to the list head at offset 0x48 in the given container (or detaches if null).
// If already attached to a different list, the node is removed from the old list first.

struct ListNode {
    int* listHead;   // +0x00 pointer to the list head node (or nullptr)
    ListNode* next;  // +0x04 next pointer in the list
};

// Detach helper (FUN_004daf90) - removes this node from its current list
void detachNodeFromList(ListNode* node);

int* __thiscall ListNode::attachToList(int* container) {
    ListNode* newHead;

    if (container == nullptr) {
        newHead = nullptr;
    } else {
        // The container stores the list head node at offset 0x48
        newHead = reinterpret_cast<ListNode*>(
            reinterpret_cast<char*>(container) + 0x48
        );
    }

    if (this->listHead != reinterpret_cast<int*>(newHead)) {
        if (this->listHead != nullptr) {
            detachNodeFromList(this);
        }

        this->listHead = reinterpret_cast<int*>(newHead);

        if (newHead != nullptr) {
            // Insert this node immediately after the list head
            this->next = newHead->next;
            newHead->next = this;
        }
    }

    return this;
}