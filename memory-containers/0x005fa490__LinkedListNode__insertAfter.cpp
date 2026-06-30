// FUNC_NAME: LinkedListNode::insertAfter
// Address: 0x005fa490
// Role: Inserts this node into a doubly-linked list after the given node.
// If this node is already in a list, it is removed first.

class LinkedListNode {
public:
    LinkedListNode* prev;  // offset 0x00
    LinkedListNode* next;  // offset 0x04
};

// Forward declaration of removal function (address 0x004daf90)
void removeNode(LinkedListNode* node);

LinkedListNode* __thiscall LinkedListNode::insertAfter(LinkedListNode* newNode) {
    if (this->prev != newNode) {
        // Remove this node from its current list if it is linked
        if (this->prev != 0) {
            removeNode(this);
        }
        // Set new previous pointer
        this->prev = newNode;
        if (newNode != 0) {
            // Link into list after newNode
            this->next = newNode->next;
            newNode->next = this;
        }
    }
    return this;
}