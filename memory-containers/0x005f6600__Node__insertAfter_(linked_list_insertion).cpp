// FUNC_NAME: Node::insertAfter (linked list insertion)
// Address: 0x005f6600
// Role: Inserts this node after the given target node in a doubly linked list.
// Assumes Node layout: +0x00 = next pointer, +0x04 = prev pointer, +0x08 = data pointer

void __thiscall Node::insertAfter(Node *targetNode)
{
    Node *nextNode = targetNode->next;  // +0x00 in targetNode
    this->next = nextNode;               // +0x00 in this
    this->prev = nullptr;                // +0x04 initially null

    if (nextNode != nullptr)
    {
        // Set this node's prev to the next node's current prev (which is targetNode in a well-formed list)
        this->prev = nextNode->prev;     // +0x04 of nextNode
        nextNode->prev = this;          // Update next node's prev to point back to this
    }

    this->data = targetNode->data;       // +0x08 copy data from targetNode (likely an object or value)
}