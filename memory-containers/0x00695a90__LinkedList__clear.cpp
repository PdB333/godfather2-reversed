// FUNC_NAME: LinkedList::clear
// Address: 0x00695a90
// Role: Clears a doubly linked list by deleting all nodes and resetting the sentinel to point to itself.

struct ListNode {
    ListNode* prev; // +0x00
    ListNode* next; // +0x04
};

struct LinkedList {
    // +0x00: unknown field (not used here)
    ListNode* sentinel; // +0x04
    int count;          // +0x08
};

// External function to delete a chain of nodes starting from a given node
void deleteNodeChain(ListNode* node);

void __fastcall LinkedList::clear(LinkedList* this) {
    ListNode* sentinel = this->sentinel;

    // Delete all nodes following the sentinel
    deleteNodeChain(sentinel->next);

    // Reset sentinel's next to point to itself
    sentinel->next = sentinel;

    // Reset count to zero
    this->count = 0;

    // Reset sentinel's prev to point to itself
    sentinel->prev = sentinel;
}