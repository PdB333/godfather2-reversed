// FUNC_NAME: Node::insertAfter
// Function address: 0x00703F70
// Intrusive doubly linked list node insertion.
// Removes 'this' from its current list (if it is already linked) and inserts it after the node referenced by 'target'.
// Node layout: +0x00: Node* prev; +0x04: Node* next

int* Node::insertAfter(int* target) {
    Node* afterNode;

    if (this != target) {
        afterNode = (Node*)*target;         // node after which to insert (from target's prev pointer)
        if (*this != afterNode) {
            if (*this != nullptr) {
                Node::removeFromList(this); // cleanup: unlink this from its current list
            }
            *this = afterNode;              // set this->prev = afterNode
            if (afterNode != nullptr) {
                this[1] = *(int*)(afterNode + 1); // set this->next = afterNode->next
                *(int**)(afterNode + 1) = this;   // set afterNode->next = this
            }
        }
    }
    return this;
}