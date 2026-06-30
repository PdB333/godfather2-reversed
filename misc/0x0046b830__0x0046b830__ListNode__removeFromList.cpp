// FUNC_NAME: 0x0046b830: ListNode::removeFromList
// Handles removal of this node from a circular singly linked list maintained by a list head structure.
// The node contains a pointer to the list head (offset 0) and a next pointer (offset 4).
// The list head stores a last pointer (offset 4). If this node is the last, update list head's last.
// Otherwise, traverse from last->next (which is first) to find the preceding node and relink.
// Optional memory deallocation if flag param_2 & 1 is set.

struct ListHead; // forward declaration

struct ListNode {
    ListHead* list; // +0x00: pointer to owning list head
    ListNode* next; // +0x04: next node in circular list (last->next == first)

    // Remove this node from its list. If deallocateFlag is non-zero, free the node.
    __thiscall ListNode* removeFromList(byte deallocateFlag);
};

struct ListHead {
    ListNode* first; // +0x00: first node (unused in this removal)
    ListNode* last;  // +0x04: last node (list is circular: last->next == first)
};

// External operator delete (likely from EARS engine)
void __cdecl operator delete(void* ptr) __attribute__((noreturn)); // signature unknown; placeholder

ListNode* __thiscall ListNode::removeFromList(byte deallocateFlag) {
    ListNode* prev;
    ListNode* curr;

    ListHead* head = this->list; // +0x00
    if (head != nullptr) {
        ListNode* lastNode = head->last; // head+0x04
        if (lastNode == this) {
            // This node is the last in the circular list; update last to its next.
            head->last = this->next;
        } else {
            // Traverse from last->next (i.e., first) to find the node before this.
            prev = lastNode;
            curr = prev->next;
            while (curr != this) {
                prev = curr;
                curr = prev->next;
            }
            // Relink: previous node skips this one.
            prev->next = this->next;
        }
    }

    // Optional deallocation.
    if ((deallocateFlag & 1) != 0) {
        operator delete(this);
    }

    return this;
}