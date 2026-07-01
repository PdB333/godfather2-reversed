// FUNC_NAME: LinkedList::advance
// Address: 0x00990df0
// Role: Advances the current pointer in a singly linked list. Resets to head if current is null.
//        Then processes the current node (via callback) and advances to next.
// Offsets:
//   +0x60: head (pointer to first node)
//   +0x84: current (pointer to current node)
// Node structure:
//   +0x00: data (size unknown)
//   +0x04: next (pointer to next node)

typedef struct ListNode {
    void* data;       // possibly data at offset 0x0
    ListNode* next;   // +0x04
} ListNode;

class LinkedList {
public:
    ListNode* head;       // +0x60
    ListNode* current;    // +0x84

    int advance();        // this function (at 0x00990df0)
};

// Forward declaration of the per-node processing function
void __thiscall processCurrentNode(LinkedList* self);

int LinkedList::advance() {
    // If current is null, reset to head
    if (current == 0) {
        current = head;
    }

    // If current is not null, process the node and move to next
    if (current != 0) {
        processCurrentNode(this);   // FUN_00990b30 – assumed to process the current node
        current = current->next;    // advance to next node
    }

    return 0; // Success (or end of list indicator)
}