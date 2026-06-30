// FUNC_NAME: EARSObject::constructor
undefined4 * __thiscall EARSObject::constructor(undefined4 *this, undefined4 param_2, undefined4 param_3)
{
    // Call base class constructor (likely EARS::BaseObject or similar)
    FUN_004ac120(param_2, param_3);

    // Initialize vtable pointer
    this[0] = &PTR_LAB_00d63e80;

    // Set member at offset 0x50 (this[0x14]) from global
    this[0x14] = DAT_00d5c454;

    // Set member at offset 0x54 (this[0x15]) from global
    this[0x15] = DAT_00d5f52c;

    // Zero out three members starting at offset 0x5C
    this[0x17] = 0;       // offset 0x5C
    this[0x18] = 0;       // offset 0x60
    // Write byte zero at offset 0x64 (low byte of this[0x19])
    *(byte *)(this + 0x19) = 0;

    // If the pointer at offset 0x48 (this[0x12]) is not null,
    // compute a derived pointer at offset 0x58 (this[0x16])
    if (this[0x12] != 0) {
        // Subtract 0x48 from that pointer (likely to get its base object)
        this[0x16] = this[0x12] - 0x48;
    } else {
        this[0x16] = 0;
    }

    return this;
}