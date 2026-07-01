// FUNC_NAME: RegisteredNode::RegisteredNode
// Address: 0x008a5e20
// Constructor for a registered node with a name, inserted into a global linked list.
// Called with a name string, and three additional parameters (likely IDs or pointers).

class RegisteredNode {
public:
    void* vtable; // +0x00
    int field_04; // +0x04 (param_3)
    int field_08; // +0x08 (param_5)
    int field_0C; // +0x0C (param_4)
    int field_10; // +0x10
    int field_14; // +0x14
    int field_18; // +0x18
    int field_1C; // +0x1C
    char name[64]; // +0x20, max 63 chars + null
    // padding from 0x60 to 0x6F (16 bytes) unknown/unused
    RegisteredNode* next; // +0x70, pointer to previous head of the list
};

// Global head of the linked list of registered nodes
RegisteredNode* gRegisteredNodeHead = (RegisteredNode*)DAT_012059ec; // from DAT_012059ec

// Base constructor called first (unknown base class)
void BaseConstructor(); // FUN_0064cc90

RegisteredNode* __thiscall RegisteredNode::RegisteredNode(RegisteredNode* this, 
                                                           const char* nameStr, 
                                                           int param3, 
                                                           int param4, 
                                                           int param5)
{
    BaseConstructor();

    // Set vtable pointer (from global constant)
    this->vtable = &PTR_LAB_00d799fc;

    // Copy the name string, up to 63 characters
    strncpy(this->name, nameStr, 0x3F);

    // Initialize fields from constructor parameters
    this->field_04 = param3;
    this->field_0C = param4;   // Note: param_4 goes to offset 0x0C
    this->field_08 = param5;   // param_5 goes to offset 0x08

    // Zero out fields 0x10 through 0x1C
    this->field_10 = 0;
    this->field_14 = 0;
    this->field_18 = 0;
    this->field_1C = 0;

    // Insert this node at the head of the global linked list
    this->next = gRegisteredNodeHead;
    gRegisteredNodeHead = this;

    return this;
}