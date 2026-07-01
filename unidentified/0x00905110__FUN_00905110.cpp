// FUNC_NAME: SomeClass::constructor
undefined4 * __thiscall SomeClass::constructor(undefined4 *this, undefined4 arg)
{
    // Call base class constructor or initialization
    FUN_00901860(arg);

    // Set vtable pointer (offset 0x00)
    *this = &PTR_FUN_00d82440;

    // Set function pointers at various offsets
    this[0x0f] = &PTR_LAB_00d82430;  // +0x3C
    this[0x12] = &PTR_LAB_00d8242c;  // +0x48
    this[0x14] = &PTR_LAB_00d82428;  // +0x50
    this[0x15] = &PTR_LAB_00d823c8;  // +0x54
    this[0x16] = &PTR_LAB_00d82360;  // +0x58

    // Global initialization call (possibly reference counting or singleton setup)
    FUN_004c14e0(1);

    return this;
}