// FUNC_NAME: MultiBaseObject::constructor
void __thiscall MultiBaseObject::constructor(MultiBaseObject *this, int arg1, int arg2)
{
    // The object layout uses multiple inheritance, with vtable pointers at +0x00 and +0x0C.
    // Initializations are done in a specific order to satisfy C++ constructor semantics.

    // Store the passed arguments into fields at +0x04 and +0x08 (likely member variables).
    this->field_04 = arg1;   // +0x04
    this->field_08 = arg2;   // +0x08

    // Temporary assignment of a base vtable pointer at +0x0C, later overwritten.
    this->vtable2 = &PTR_FUN_00e2f19c;  // +0x0C (temp)

    // Initialize a flag and a counter.
    this->field_10 = 1;      // +0x10 – likely a flag (e.g., active)
    this->field_14 = 0;      // +0x14 – likely a counter or state

    // Set the primary vtable pointer at +0x00.
    this->vtable1 = &PTR_FUN_00e358b8;  // +0x00 (primary vtable)

    // Overwrite the secondary vtable pointer at +0x0C with the real one.
    this->vtable2 = &PTR_LAB_00e35940;  // +0x0C (secondary vtable)

    // Zero out remaining fields.
    this->field_18 = 0;      // +0x18 – uninitialized data
    this->field_1C = 0;      // +0x1C
    this->field_20 = 0;      // +0x20
    this->field_24 = 0;      // +0x24
    this->field_28 = 0;      // +0x28 – single byte
}