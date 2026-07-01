// FUNC_NAME: BaseClass::BaseClass
undefined4 * __fastcall BaseClass::BaseClass(undefined4 *this) {
    // Call base class constructor
    SomeBase::SomeBase(); // FUN_007aaaa0 - assumed base constructor
    // Set vtable
    *this = &PTR_FUN_00d6e930; // vtable for BaseClass
    // Initialize fields to 0
    this[2] = 0; // +0x08
    this[3] = 0; // +0x0C
    this[10] = 0; // +0x28
    *(undefined1 *)(this + 0x10) = 0; // byte at +0x40 (since this is int*, offset 0x40)
    this[6] = 0; // +0x18
    this[5] = 0; // +0x14
    this[4] = 0; // +0x10
    this[9] = 0; // +0x24
    this[8] = 0; // +0x20
    this[7] = 0; // +0x1C
    return this;
}