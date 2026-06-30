// FUNC_NAME: NodeList::processAndClear
// Function address: 0x006faf00
// Role: Iterates a linked list of nodes, calling a manager's release method on each,
// then clears the list head, tail, and count to zero.

typedef struct Node Node;
struct Node {
    int field_0;          // +0x00
    int field_4;          // +0x04
    Node* next;           // +0x08
};

struct Manager {
    void** vtable;        // +0x00
    // vtable[1] = void releaseNode(Node* node, int flags)
};

struct NodeList {
    Node* head;           // +0x00
    Node* tail;           // +0x04
    int count;            // +0x08
    Manager* manager;     // +0x10
};

// __thiscall
void __fastcall NodeList::processAndClear(NodeList* this) {
    Node* node;

    node = this->head;
    while (node != 0) {
        this->tail = node->next;                    // store next before release
        this->manager->vtable[1](node, 0);          // call releaseNode(node, 0)
        node = this->tail;                          // advance to next
        this->head = node;                          // update head
    }
    this->tail = 0;
    this->head = 0;
    this->count = 0;
}