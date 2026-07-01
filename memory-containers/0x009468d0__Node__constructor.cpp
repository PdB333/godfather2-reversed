// FUNC_NAME: Node::constructor

class Node {
public:
    void *vtable;        // +0x00
    uint32_t data1;      // +0x04
    uint32_t data2;      // +0x08
    uint32_t data3;      // +0x0C
    uint32_t reserved[4];// +0x10 – +0x1C
    char name[64];       // +0x20 (max 63 chars)
    // padding/other fields up to +0x70
    Node *next;          // +0x70 (linked list pointer)
};

Node* __thiscall Node::Node(Node *this, const char *name, uint32_t data1Val, uint32_t data3Val, uint32_t data2Val) {
    // Base class constructor (likely initializes vtable and other base members)
    FUN_0064cc90();

    // Set vtable pointer (global)
    this->vtable = &PTR_LAB_00d8b498;

    // Copy name string (64-byte buffer, null-terminated, max 63 characters)
    _strncpy(this->name, name, 0x3f);

    // Store three parameters into fields
    this->data1 = data1Val;   // +0x04
    this->data3 = data3Val;   // +0x0C (note: param_1[3] = param_4)
    this->data2 = data2Val;   // +0x08 (param_1[2] = param_5)

    // Zero out reserved fields (offset +0x10 through +0x1C)
    this->reserved[0] = 0;
    this->reserved[1] = 0;
    this->reserved[2] = 0;
    this->reserved[3] = 0;

    // Link this node into the global singly-linked list (head pointer at DAT_012059ec)
    this->next = DAT_012059ec;   // previous head becomes this->next
    DAT_012059ec = this;         // now this is the new head

    return this;
}