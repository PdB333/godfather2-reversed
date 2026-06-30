// FUNC_NAME: Entity::Entity
// Function address: 0x006be1d0
// Role: Constructor for Entity (or derived class) initializing base class, vtable pointers, and zeroing fields.

int* __thiscall Entity::Entity(int* this, int param)
{
    // Call base class constructor (likely EARSObject or similar)
    FUN_0046c590(param);

    // Set main vtable pointer
    *this = (int)&PTR_FUN_00d5eb30;

    // Set additional interface/vtable pointers for multiple inheritance
    this[0x0F] = (int)&PTR_LAB_00d5eb20; // +0x3C
    this[0x12] = (int)&PTR_LAB_00d5eb1c; // +0x48

    // Zero out member fields
    this[0x14] = 0; // +0x50 (int)
    this[0x15] = 0; // +0x54 (int)
    this[0x16] = 0; // +0x58 (int)

    // Halfword fields at +0x5C and +0x5E (likely short pair or packed)
    *(short*)((char*)this + 0x5C) = 0; // +0x5C
    *(short*)((char*)this + 0x5E) = 0; // +0x5E

    this[0x18] = 0; // +0x60 (int)

    // Another halfword pair at +0x64, +0x66
    *(short*)((char*)this + 0x64) = 0; // +0x64
    *(short*)((char*)this + 0x66) = 0; // +0x66

    this[0x1A] = 0; // +0x68 (int)

    // Halfword pair at +0x6C, +0x6E
    *(short*)((char*)this + 0x6C) = 0; // +0x6C
    *(short*)((char*)this + 0x6E) = 0; // +0x6E

    this[0x1C] = 0; // +0x70 (int)

    return this;
}