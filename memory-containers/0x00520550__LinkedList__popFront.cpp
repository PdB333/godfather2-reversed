// FUNC_NAME: LinkedList::popFront
// Address: 0x00520550
// This function removes and returns the first node from a doubly linked list.
// The list container has head at this+0x20 and tail at this+0x28.
// Each node has a vtable pointer at offset 0, prev at +0x40, next at +0x44,
// and a flag at +0xD0 (node[0x34]).
// After removal, if the flag is non-zero, a cleanup function is called (0x0066dfe0).
// Then the second virtual function (vtable[1]) is invoked on the node.

// Forward declarations
struct LinkedListNode; // Node with vtable pointer at offset 0
void cleanupFunction(); // FUN_0066dfe0

struct LinkedListNode {
    int* vftable;       // +0x00
    // ... other fields ...
    LinkedListNode* prev; // +0x40 (offset 0x10 in int units)
    LinkedListNode* next; // +0x44 (offset 0x11 in int units)
    int flag;            // +0xD0 (offset 0x34 in int units)
    // ... possibly more ...
};

class LinkedList {
public:
    LinkedListNode* head; // +0x20
    LinkedListNode* tail; // +0x28
    // ... other fields ...

    LinkedListNode* popFront();
};

// Implementation
LinkedListNode* LinkedList::popFront() {
    LinkedListNode* node = this->head;
    if (node != this->tail) {
        // Unlink node from list
        node->next->prev = node->prev;
        node->prev->next = node->next;

        if (node->flag != 0) {
            cleanupFunction();
            node->flag = 0;
        }

        // Call second virtual function (e.g., release or destructor)
        (*(void (**)())(node->vftable[1]))();

        return node;
    }
    return nullptr;
}