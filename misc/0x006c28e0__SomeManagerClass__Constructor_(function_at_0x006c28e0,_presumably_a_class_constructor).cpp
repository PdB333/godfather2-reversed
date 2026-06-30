// FUNC_NAME: SomeManagerClass::Constructor (function at 0x006c28e0, presumably a class constructor)
// Sets vtable pointer at +0x00, initializes several fields at offsets 0x3C, 0x48, 0x50, 0x58, 0x5C, 0x60, 0x64 (see offsets below)
// Calls FUN_00473840 (likely base class constructor using param_2) and FUN_006c1360

undefined4* __thiscall SomeManagerClass::Constructor(undefined4* this, undefined4 param_2)
{
    // Call base class constructor? param_2 might be an initialization argument
    FUN_00473840(param_2);

    // Set virtual table pointer at +0x00
    *this = &PTR_FUN_00d5ef08;

    // Set function pointers or vtable overrides at various offsets
    // +0x3C (15 words * 4 = 60 bytes)
    this[0xf] = &PTR_LAB_00d5eef8;
    // +0x48 (18 words * 4 = 72 bytes)
    this[0x12] = &PTR_LAB_00d5eef4;
    // +0x50 (20 words * 4 = 80 bytes)
    this[0x14] = &PTR_LAB_00d5eef0;

    // Zero out fields at +0x58, +0x5C, +0x60, +0x64
    this[0x16] = 0;  // +0x58
    this[0x17] = 0;  // +0x5C
    this[0x18] = 0;  // +0x60
    this[0x19] = 0;  // +0x64

    // Another initialization call
    FUN_006c1360();

    return this;
}