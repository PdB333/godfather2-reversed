// FUNC_NAME: Node::insertBefore
// Address: 0x004d1e60
// Inserts a new node before the current node (this) in a doubly linked list.
// newNode is the node to insert (originally passed in EAX register, but represented as a parameter here).
// head is a pointer to the list head pointer, updated if inserting at the front.
void __thiscall Node::insertBefore(Node** head, Node* newNode) {
    // new node's next points to this node
    newNode->next = this;
    // new node's prev becomes this node's previous
    newNode->prev = this->prev;

    Node* prevNode = this->prev;
    if (prevNode == nullptr) {
        // inserting at front – update head pointer
        *head = newNode;
    } else {
        // previous node's next now points to the new node
        prevNode->next = newNode;
    }

    // this node's previous becomes the new node
    this->prev = newNode;
}