// FUNC_NAME: EARSObject::constructor
// Address: 0x006b7af0
// Role: Base object constructor setting vtables and calling initializers

void __thiscall EARSObject::constructor(EARSObject *this)
{
    // Set primary vtable pointer at offset 0
    this->vtable = &PTR_FUN_00d5e588;
    // Set secondary vtable pointers at offsets 0x3C and 0x48 (interface vtables?)
    this->field_0x3c = &PTR_LAB_00d5e578; // +0x3C
    this->field_0x48 = &PTR_LAB_00d5e574; // +0x48
    // Call base initialization functions
    FUN_004086d0(&DAT_0120e93c); // Possibly a global singleton init
    FUN_0046c640();              // Additional setup
}