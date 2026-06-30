// FUNC_NAME: DoublyLinkedListNode::insertBefore
// Address: 0x005f5c20
// Role: Inserts this node before a given node in a doubly linked list, or initializes as standalone if given node is null.

struct DoublyLinkedListNode {
    DoublyLinkedListNode* next;   // +0x00
    DoublyLinkedListNode* prev;   // +0x04
    int data;                     // +0x08
};

void __thiscall DoublyLinkedListNode::insertBefore(DoublyLinkedListNode* this, DoublyLinkedListNode* node, int value) {
    // Initialize next and prev to null
    this->next = nullptr;
    this->prev = nullptr;

    if (node != nullptr) {
        // Insert this node before the given node
        this->next = node;
        this->prev = node->prev;          // node->prev is at offset +0x04
        node->prev = this;                // Update node's prev to point to this
    }

    // Store the data value
    this->data = value;
}