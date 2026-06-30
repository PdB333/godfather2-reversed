// FUNC_NAME: SomeClass::SomeClass
// Address: 0x006d5db0
// Role: Constructor for a game object class (likely from EA EARS engine).
// Initializes base class via FUN_0046c590, sets vtable pointer and function pointers,
// and zeros out several fields (counters/flags/pointers).

undefined4 * __thiscall SomeClass::SomeClass(undefined4 *this, undefined4 param_2)
{
    // Call base class constructor (FUN_0046c590)
    FUN_0046c590(param_2);

    // Set vtable pointer at offset 0x00
    *this = &PTR_FUN_00d5f42c;

    // Set function pointer at offset +0x3C (0xF * 4)
    this[0xF] = &PTR_LAB_00d5f41c;

    // Set function pointer at offset +0x48 (0x12 * 4)
    this[0x12] = &PTR_LAB_00d5f418;

    // Zero out fields from offset +0x50 to +0x68
    this[0x14] = 0;                       // +0x50: int (counter?)
    *(undefined2 *)(this + 0x15) = 0;     // +0x54: short
    *(undefined2 *)((int)this + 0x56) = 0; // +0x56: short
    this[0x19] = 0;                       // +0x64: int
    this[0x18] = 0;                       // +0x60: int
    this[0x17] = 0;                       // +0x5C: int
    this[0x16] = 0;                       // +0x58: int
    this[0x1A] = 0;                       // +0x68: int

    return this;
}