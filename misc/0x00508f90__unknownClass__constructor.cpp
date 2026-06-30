// FUNC_NAME: unknownClass::constructor
// Address: 0x00508f90 — Initializes an unknown class instance (constructor)
// Based on decompilation: sets vtable pointer, flags, and several fields to 0;
// also writes 0xFFFFFFFF at offset 0x1C and 0 at offset 0xA0, then sets bits 0 and 1 in field_8.

void __thiscall unknownClass::constructor(unknownClass* this) // param_1 is ECX = this
{
    this->vtable = &PTR_FUN_00e380b0;    // +0x00: vtable pointer
    this->field_4 = 0;                    // +0x04
    this->field_8 = 0;                    // +0x08 (flags, later ORed with 3)
    this->field_C = 0;                    // +0x0C
    this->field_10 = 0;                   // +0x10
    this->field_14 = 0;                   // +0x14
    this->field_18 = 0;                   // +0x18
    this->field_1C = 0xFFFFFFFF;          // +0x1C: initialized to -1
    this->field_A0 = 0;                   // +0xA0 (offset 0x28 * 4)

    this->field_8 |= 3;                   // set bits 0 and 1 (e.g., enable flags)
}