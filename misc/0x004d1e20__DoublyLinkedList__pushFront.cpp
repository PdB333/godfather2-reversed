// FUNC_NAME: DoublyLinkedList::pushFront

// Function address: 0x004d1e20
// Role: Insert a node at the front of a doubly-linked list with head and tail pointers.
// List structure offsets: +0x00 = head, +0x04 = tail
// Node structure offsets: +0x00 = next, +0x04 = prev

struct DoublyLinkedNode {
    DoublyLinkedNode* next;   // +0x00
    DoublyLinkedNode* prev;   // +0x04
};

struct DoublyLinkedList {
    DoublyLinkedNode* head;   // +0x00
    DoublyLinkedNode* tail;   // +0x04
};

void __thiscall DoublyLinkedList::pushFront(DoublyLinkedNode* node) {
    node->next = this->head;
    node->prev = 0;

    if (this->head != 0) {
        // List non-empty: link current head's prev to new node, then update head
        this->head->prev = node;
        this->head = node;
    } else {
        // List empty: both head and tail become the new node
        this->tail = node;
        this->head = node;
    }
}