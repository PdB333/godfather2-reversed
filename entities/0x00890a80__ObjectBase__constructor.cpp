// FUNC_NAME: ObjectBase::constructor
undefined4 * __thiscall ObjectBase::constructor(undefined4 *this, undefined4 param_2)
{
    // Call base initialization with size 0x4000
    FUN_0046e6b0(param_2, 0x4000);
    
    // Zero out fields at offsets 0x1C0 and 0x1C4 (byte)
    this[0x70] = 0;                               // +0x1C0: int field
    *(undefined1 *)(this + 0x71) = 0;              // +0x1C4: byte field

    // Set vtable pointer
    *this = &PTR_FUN_00d775c8;                     // +0x00: vtable

    // Set additional function pointers / tables
    this[0xf] = &PTR_LAB_00d775b8;                 // +0x3C
    this[0x12] = &PTR_LAB_00d775b4;               // +0x48
    this[0x14] = &PTR_LAB_00d775b0;               // +0x50
    this[0x15] = &PTR_LAB_00d77550;               // +0x54
    this[0x16] = &PTR_LAB_00d774e8;               // +0x58

    return this;
}