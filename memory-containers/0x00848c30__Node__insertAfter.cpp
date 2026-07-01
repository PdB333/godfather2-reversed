// FUNC_NAME: Node::insertAfter
// Address: 0x00848c30
// Role: Inserts this node after a given previous node in a doubly linked list.
//        Sets this->next to null (making it the tail) and updates the previous node's next pointer.
//        If prevNode is null, this node becomes the head.
// Structure offsets: +0x00: data (unused here), +0x04: next, +0x08: prev
void __thiscall Node::insertAfter(Node* prevNode)
{
    this->next = 0;
    this->prev = prevNode;
    if (prevNode != 0) {
        prevNode->next = this;
    }
    return;
}