// FUNC_NAME: NodeList::removeNode

// Node structure assumed to have a 'next' pointer at offset 0x10
struct Node {
    // unknown fields before 0x10
    // ...
    Node* next;  // +0x10
};

// List structure with head and tail pointers
class NodeList {
public:
    Node* head; // +0x00
    Node* tail; // +0x04

    __thiscall void removeNode(Node* node);
};

void __thiscall NodeList::removeNode(Node* node) {
    if (node != nullptr) {
        // If node is the tail, update tail to its successor
        if (this->tail == node) {
            this->tail = node->next; // dereference +0x10
        }
        // If node is the head, update head to its successor
        if (this->head == node) {
            this->head = node->next; // dereference +0x10
        }
        // Call cleanup/deallocation routine for the removed node
        // TODO: identify FUN_005c2e30 (likely freeNode or destructor)
        ::FUN_005c2e30();
    }
}