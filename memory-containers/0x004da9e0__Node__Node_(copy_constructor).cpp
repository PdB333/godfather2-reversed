// FUNC_NAME: Node::Node (copy constructor)
// Address: 0x004da9e0
// Deep-copies a linked list node structure with fields at offsets +0x00, +0x08, +0x0A, +0x0C, +0x10, and +0x14 (next pointer).

struct Node {
    uint64_t data0;      // +0x00
    int16_t  data1;      // +0x08
    uint8_t  data2;      // +0x0A
    // padding at +0x0B
    int32_t  data3;      // +0x0C
    int32_t  data4;      // +0x10
    Node*    next;       // +0x14
};

void __thiscall Node::Node(Node* this, const Node* source) {
    // Initialize next pointer to null (default)
    this->next = nullptr;

    // Shallow copy of all non‑pointer fields
    this->data0 = source->data0;
    this->data1 = source->data1;
    this->data2 = source->data2;
    this->data3 = source->data3;
    this->data4 = source->data4;

    // Recursively deep copy the linked list
    if (source->next != nullptr) {
        Node* newNode = (Node*)operator new(0x18); // custom allocator (size 0x18)
        if (newNode != nullptr) {
            newNode->Node(source->next);            // recursive copy constructor call
            this->next = newNode;
        } else {
            this->next = nullptr;                  // allocation failed, keep null
        }
    }
}