// FUNC_NAME: SomeClass::SomeClass

// Constructor for SomeClass (address 0x0091d790)
// Initializes vtable pointers and zeros a specific range of fields
SomeClass* __fastcall SomeClass::SomeClass(SomeClass* this) {
    // Call base class constructor (likely a parent class initializer)
    FUN_005bf9b0(); // BaseClass::BaseClass()

    // Set primary vtable pointer at offset 0x00
    this->vtable = &PTR_FUN_00d85b30; // +0x00

    // Set secondary vtable pointer at offset 0x10
    this->secondaryVtable = &PTR_LAB_00d85b0c; // +0x10

    // Zero out fields from offset 0x4C to 0x84 (15 dwords)
    this->field_0x4C = 0; // +0x4C
    this->field_0x50 = 0; // +0x50
    this->field_0x54 = 0; // +0x54
    this->field_0x58 = 0; // +0x58
    this->field_0x5C = 0; // +0x5C
    this->field_0x60 = 0; // +0x60
    this->field_0x64 = 0; // +0x64
    this->field_0x68 = 0; // +0x68
    this->field_0x6C = 0; // +0x6C
    this->field_0x70 = 0; // +0x70
    this->field_0x74 = 0; // +0x74
    this->field_0x78 = 0; // +0x78
    this->field_0x7C = 0; // +0x7C
    this->field_0x80 = 0; // +0x80
    this->field_0x84 = 0; // +0x84

    // Zero a byte at offset 0x94
    *(uint8_t*)((uintptr_t)this + 0x94) = 0; // +0x94

    // Zero dwords at offsets 0x98, 0x9C, 0xA0, 0xA4
    this->field_0x98 = 0; // +0x98
    this->field_0x9C = 0; // +0x9C
    this->field_0xA0 = 0; // +0xA0
    this->field_0xA4 = 0; // +0xA4

    return this;
}