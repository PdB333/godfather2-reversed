// FUNC_NAME: RegisteredObjectNode::RegisteredObjectNode
// Constructor for a registered object node with name, two IDs, and a type flag.
// Appends itself to a global singly linked list of RegisteredObjectNodes.
// vtable at +0x00, name buffer at +0x20 (63 bytes), id1 at +0x04, id2 at +0x0C, type at +0x08,
// next pointer at +0x70 (offset 0x1c * 4 = 0x70), other fields (0x10-0x1C) unused/zero.

class RegisteredObjectNode;
extern RegisteredObjectNode* g_objectListHead; // DAT_012059ec

class RegisteredObjectNode {
public:
    // vtable pointer at offset 0
    void* vtable;                              // +0x00
    uint32_t id1;                              // +0x04  param_3
    uint32_t type;                             // +0x08  param_5
    uint32_t id2;                              // +0x0C  param_4
    uint32_t unknown10;                        // +0x10  always 0
    uint32_t unknown14;                        // +0x14  always 0
    uint32_t unknown18;                        // +0x18  always 0
    uint32_t unknown1C;                        // +0x1C  always 0
    char name[63];                             // +0x20
    // padding? maybe 1 byte for alignment? but strncpy writes 63 bytes, so likely packed.
    RegisteredObjectNode* next;                // +0x70  *param_1 + 0x1c
};

RegisteredObjectNode* __thiscall RegisteredObjectNode::RegisteredObjectNode(
    char* name, uint32_t id1, uint32_t id2, uint32_t type)
{
    // Call base class constructor (likely does nothing beyond vtable setup)
    // FUN_0064cc90 is assumed to be Base::Base()
    FUN_0064cc90();

    // Set vtable to the class's vtable (unique per class type)
    this->vtable = &PTR_LAB_00d7e0a0;

    // Copy name into buffer (max 63 chars, null-terminated by strncpy)
    _strncpy(this->name, name, 0x3f);

    // Store IDs and type
    this->id1 = id1;     // param_3
    this->type = type;   // param_5
    this->id2 = id2;     // param_4

    // Zero out unused/uninitialized fields
    this->unknown10 = 0;
    this->unknown14 = 0;
    this->unknown18 = 0;
    this->unknown1C = 0;

    // Insert this node at head of global object list
    this->next = g_objectListHead;
    g_objectListHead = this;

    return this;
}