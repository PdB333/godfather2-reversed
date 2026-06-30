// FUNC_NAME: ListNode::unlink

// Function address: 0x00647e40
// Removes this node from a doubly-linked list by directly updating the neighbor pointers.
// Offsets: +0x18 = next, +0x1c = prev

class ListNode {
public:
    ListNode* next;   // +0x18
    ListNode* prev;   // +0x1c

    // Unlink this node from the list (assumes non-null neighbors)
    void __thiscall unlink() {
        prev->next = next;   // Previous node's next now points to this node's next
        next->prev = prev;   // Next node's prev now points to this node's prev
    }
};