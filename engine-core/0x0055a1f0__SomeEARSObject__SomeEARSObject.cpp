// FUNC_NAME: SomeEARSObject::SomeEARSObject
// Address: 0x0055a1f0
// Role: Constructor for a class with two virtual tables (multiple inheritance).
// Sets up vtable pointers, copies global constants, and zeroes several fields.
void __thiscall SomeEARSObject::SomeEARSObject(SomeEARSObject *this)
{
    uint32_t global1 = DAT_00e2b1a4;   // +0x?? Global constant (likely a singleton pointer)
    uint32_t global2 = DAT_00e446bc;   // +0x?? Global constant

    // Primary vtable at offset 0
    this->vtable0 = &PTR_FUN_00e3a038;

    // Temporary base-class vtable (overwritten below)
    this->vtable1_temp = &PTR_LAB_00dc3dd4;

    // Copy global values into fields at offsets 0x8, 0xC, 0x10, 0x14, 0x18
    this->field_0x08 = global1; // +0x08
    this->field_0x0C = global1; // +0x0C
    this->field_0x10 = global2; // +0x10
    this->field_0x14 = global2; // +0x14
    this->field_0x18 = global2; // +0x18

    // Final secondary vtable (overwrites temporary base vtable)
    this->vtable1 = &PTR_LAB_00e3a054; // +0x04

    // Zero out fields at offsets 0x1C, 0x20, 0x24, 0x28, 0x2C, 0x30, 0x34
    this->field_0x34 = 0; // index 0xD
    this->field_0x24 = 0; // index 0x9
    this->field_0x28 = 0; // index 0xA
    this->field_0x2C = 0; // index 0xB
    this->field_0x1C = 0; // index 0x7
    this->field_0x30 = 0; // index 0xC
    this->field_0x20 = 0; // index 0x8
}