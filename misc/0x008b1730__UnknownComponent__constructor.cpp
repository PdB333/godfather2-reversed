// FUNC_NAME: UnknownComponent::constructor
// Function address: 0x008b1730
// Role: Constructor for a class with multiple vtable pointers (base + two interfaces)
// Offsets: vtable at +0x00, vtable2 at +0x3C, vtable3 at +0x48, int at +0x50, shorts at 0x54/0x56, int at +0x58, shorts at 0x5C/0x5E

struct UnknownComponent {
    // +0x00: vtable pointer for primary class (PTR_FUN_00d7ab60)
    void** vtable;
    // +0x04 to +0x38: other members (unknown)
    // +0x3C: second vtable pointer (PTR_LAB_00d7ab50)
    void** vtable2;
    // +0x40 to +0x44: padding/members
    // +0x48: third vtable pointer (PTR_LAB_00d7ab4c)
    void** vtable3;
    // +0x4C: unknown
    // +0x50: int field, initialized to 0
    int field_0x50;
    // +0x54: short, initialized to 0
    short field_0x54;
    // +0x56: short, initialized to 0
    short field_0x56;
    // +0x58: int field, initialized to 0
    int field_0x58;
    // +0x5C: short, initialized to 0
    short field_0x5C;
    // +0x5E: short, initialized to 0
    short field_0x5E;
};

// Forward declaration of base constructor
int FUN_0046c590(int param);

// Constructor
UnknownComponent* __thiscall UnknownComponent::constructor(UnknownComponent* this, int param_2) {
    // Call base class constructor or initialization function
    FUN_0046c590(param_2);

    // Set primary vtable
    this->vtable = (void**)0x00d7ab60;
    // Set secondary vtable pointers for interfaces
    this->vtable2 = (void**)0x00d7ab50;
    this->vtable3 = (void**)0x00d7ab4c;

    // Zero-initialize fields
    this->field_0x50 = 0;
    this->field_0x54 = 0;
    this->field_0x56 = 0;
    this->field_0x58 = 0;
    this->field_0x5C = 0;
    this->field_0x5E = 0;

    return this;
}