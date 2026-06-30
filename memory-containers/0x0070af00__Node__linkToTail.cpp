// FUNC_NAME: Node::linkToTail
// Address: 0x0070af00
// This function links a Node to the tail of a doubly-linked list owned by a Container.
// The container has a sentinel (dummy) node at offset 0x48, whose 'next' points to the first node and 'prev' to the last.
// Inserting before the sentinel effectively adds the node to the tail.
// If the node is already at the tail (node->next == sentinel) the function does nothing.
// Otherwise, it unlinks the node from any previous list and inserts it at the tail.

class Node {
public:
    Node* _next;    // +0x00
    Node* _prev;    // +0x04

    // Unlink this node from its current list (called by linkToTail if needed)
    void unlink();
};

class Container {
    // ... other members up to 0x48
    Node _sentinel; // +0x48 (dummy node, its next/prev at +0x48/+0x4C)
};

Node* __thiscall Node::linkToTail(Container* container)
{
    Node* sentinel;

    if (container == nullptr) {
        sentinel = nullptr;
    } else {
        sentinel = reinterpret_cast<Node*>(reinterpret_cast<uint8_t*>(container) + 0x48);
    }

    // If node is already the tail of this list (i.e., its next points to the sentinel), skip.
    if (this->_next != sentinel) {
        // Remove node from its current list if it is linked.
        if (this->_next != nullptr) {
            this->unlink();
        }

        // Link node to the tail of the new list.
        this->_next = sentinel;                     // point to sentinel (makes it the last node)
        if (sentinel != nullptr) {
            this->_prev = sentinel->_prev;          // previous node becomes old tail
            sentinel->_prev = this;                 // sentinel's prev now points to this (new tail)
        }
    }

    return this;
}