//FUNC_NAME: UnknownClass::constructor

// Constructor for an unknown class at 0x008b2650.
// Initializes vtable pointers and zeroes several fields.
// Calls base constructor FUN_0046c590 with the given argument.

undefined4 * __thiscall UnknownClass::constructor(undefined4 *this, undefined4 arg)
{
    // Call base class constructor (likely a parent class)
    FUN_0046c590(arg);

    // Set vtable pointer for this class
    *this = &PTR_FUN_00d7ace4;

    // Set additional vtable-like pointers at offsets 0x3C and 0x48
    this[0xf] = &PTR_LAB_00d7acd4;   // +0x3C
    this[0x12] = &PTR_LAB_00d7acd0;  // +0x48

    // Zero out various fields (shorts and ints)
    *(undefined2 *)(this + 0x16) = 0;   // +0x58 (short)
    *(undefined2 *)((int)this + 0x5a) = 0; // +0x5A (short)
    *(undefined2 *)(this + 0x18) = 0;   // +0x60 (short)
    *(undefined2 *)((int)this + 0x62) = 0; // +0x62 (short)
    this[0x15] = 0;   // +0x54 (int)
    this[0x17] = 0;   // +0x5C (int)

    return this;
}