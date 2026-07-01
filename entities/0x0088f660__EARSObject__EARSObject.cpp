// FUNC_NAME: EARSObject::EARSObject
// Function address: 0x0088f660
// Role: Constructor for EARSObject, sets vtable pointers and initializes members

undefined4 * __thiscall EARSObject::EARSObject(undefined4 *this, undefined4 arg1, undefined4 arg2)
{
    undefined4 uVar1;
    
    // Call base class constructor (likely another base)
    FUN_004b9e70(arg1, arg2);

    // vtable: +0x00 (primary)
    *this = &PTR_FUN_00d77360;

    // vtable pointers at various offsets (multiple inheritance / interfaces)
    // +0x3C = offset 0x0F * 4
    this[0x0F] = &PTR_LAB_00d77350; // +0x3C
    // +0x48 = offset 0x12 * 4
    this[0x12] = &PTR_LAB_00d7734c; // +0x48
    // +0x50 = offset 0x14 * 4
    this[0x14] = &PTR_LAB_00d77348; // +0x50
    // +0x54 = offset 0x15 * 4
    this[0x15] = &PTR_LAB_00d772e8; // +0x54
    // +0x58 = offset 0x16 * 4
    this[0x16] = &PTR_LAB_00d77280; // +0x58

    // Clear fields at offsets 0x1C0 (0x70*4) and 0x1C4 (0x71*4)
    this[0x70] = 0; // +0x1C0
    this[0x71] = 0; // +0x1C4

    // Short field at offset 0x1C8 (0x72*4 = 0x1C8, but short => 2 bytes)
    *(undefined2 *)(this + 0x72) = 0; // +0x1C8

    // Byte field at offset 0x1CA
    *(undefined1 *)((int)this + 0x1CA) = 0; // +0x1CA

    // Int fields at offsets 0x1CC (0x73*4) and 0x1D0 (0x74*4)
    this[0x73] = 0; // +0x1CC
    this[0x74] = 0; // +0x1D0

    // Call some function to get a handle/ID, store at +0x1D4 (0x75*4)
    uVar1 = FUN_0042b400();
    this[0x75] = uVar1; // +0x1D4

    // Clear fields at +0x1D8 (0x76*4) and +0x1DC (0x77*4)
    this[0x76] = 0; // +0x1D8
    this[0x77] = 0; // +0x1DC

    return this;
}