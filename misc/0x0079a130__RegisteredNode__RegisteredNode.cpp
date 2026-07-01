// FUNC_NAME: RegisteredNode::RegisteredNode
// Address: 0x0079a130
// Constructor for a registered node that is inserted into a global linked list.
// The class has a vtable, a name string (max 63 chars), three data fields, and a next pointer.
// The global head pointer (DAT_012059ec) is updated to point to the new node.

class RegisteredNode {
public:
    // Vtable pointer at offset 0x00
    void* vtable;
    // Data fields at offsets 0x04, 0x08, 0x0C? Actually offsets: param_1[1] = +0x04, param_1[2] = +0x08, param_1[3] = +0x0C
    // But note: param_1[1] gets param_3, param_1[2] gets param_5, param_1[3] gets param_4.
    // So the order of parameters is not sequential.
    int field_0x04; // +0x04
    int field_0x08; // +0x08
    int field_0x0C; // +0x0C
    // Name buffer at offset 0x10 (param_1 + 8) - 64 bytes (0x40)
    char name[64]; // +0x10
    // Zeroed fields at offsets 0x50, 0x54, 0x58, 0x5C? Actually param_1[4] to [7] = +0x10, +0x14, +0x18, +0x1C? Wait, param_1 is int*, so param_1[4] is at offset 0x10? No, param_1 is undefined4*, so each element is 4 bytes. param_1[4] is offset 0x10, param_1[5] offset 0x14, param_1[6] offset 0x18, param_1[7] offset 0x1C. But we already have name at param_1+8 (offset 0x20? Actually param_1+8 is pointer arithmetic: param_1 is undefined4*, so adding 8 gives offset 0x20 bytes. That would place name at offset 0x20. Let's recalc: param_1 is a pointer to undefined4 (4 bytes). param_1[0] is offset 0, param_1[1] offset 4, param_1[2] offset 8, param_1[3] offset 12, param_1[4] offset 16, param_1[5] offset 20, param_1[6] offset 24, param_1[7] offset 28, param_1[8] offset 32 (0x20). So name starts at offset 0x20. Then param_1[0x1c] is offset 0x70 (28*4=112=0x70). So the next pointer is at offset 0x70. The zeroed fields are at offsets 0x10, 0x14, 0x18, 0x1C (param_1[4] to [7]). So the layout is:
    // +0x00: vtable
    // +0x04: field_0x04 (from param_3)
    // +0x08: field_0x08 (from param_5)
    // +0x0C: field_0x0C (from param_4)
    // +0x10: zero1
    // +0x14: zero2
    // +0x18: zero3
    // +0x1C: zero4
    // +0x20: name[64] (0x40 bytes)
    // +0x60: ? (maybe padding)
    // +0x70: next pointer
    int zero1; // +0x10
    int zero2; // +0x14
    int zero3; // +0x18
    int zero4; // +0x1C
    char name[64]; // +0x20
    // Possibly padding to align next to 0x70? But we'll just define next at +0x70.
    RegisteredNode* next; // +0x70
};

// Global head of the linked list (DAT_012059ec)
extern RegisteredNode* g_registeredNodeHead;

// Constructor
RegisteredNode* __thiscall RegisteredNode::RegisteredNode(RegisteredNode* this, const char* name, int value1, int value2, int value3) {
    // Call base class constructor (FUN_0064cc90) - likely initializes vtable or other base members
    FUN_0064cc90(); // Assume this sets up some base class

    // Set vtable
    this->vtable = &PTR_LAB_00d6a6d4;

    // Copy name with max length 63 (0x3f) - note: strncpy does not null-terminate if source is longer, but we assume it's safe
    _strncpy(this->name, name, 0x3f);

    // Set data fields (note the parameter order: value1 goes to field_0x04, value3 goes to field_0x08, value2 goes to field_0x0C)
    this->field_0x04 = value1;  // param_3
    this->field_0x0C = value2;  // param_4
    this->field_0x08 = value3;  // param_5

    // Zero out four fields
    this->zero1 = 0;
    this->zero2 = 0;
    this->zero3 = 0;
    this->zero4 = 0;

    // Link into global list: set next to current head, then update head to this
    this->next = g_registeredNodeHead;
    g_registeredNodeHead = this;

    return this;
}