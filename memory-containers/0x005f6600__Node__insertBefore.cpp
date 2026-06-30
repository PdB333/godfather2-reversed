// FUNC_NAME: Node::insertBefore
struct Node {
    void* value; // +0x00
    Node* next;  // +0x04
    Node* prev;  // +0x08
};

void __thiscall Node::insertBefore(Node* refNode) {
    void* oldValue = refNode->value;
    this->value = oldValue;
    this->next = nullptr;
    if (oldValue != nullptr) {
        // oldValue points to an object whose next pointer at +0x04 is being updated
        this->next = reinterpret_cast<Node*>(oldValue)->next;
        reinterpret_cast<Node*>(oldValue)->next = this;
    }
    this->prev = refNode->prev;
}