// FUNC_NAME: ConstructMultiVTableObject
undefined4 * __thiscall ConstructMultiVTableObject(undefined4 *this, undefined4 param2)
{
    // Call base class constructor (FUN_0046c590) with the provided parameter
    FUN_0046c590(param2);

    // Set vtable pointer at offset 0x00
    *this = &PTR_FUN_00d5eb30;

    // Set function table pointers at offsets +0x3C and +0x48
    this[0xf] = &PTR_LAB_00d5eb20;   // +0x3C: function table
    this[0x12] = &PTR_LAB_00d5eb1c;  // +0x48: function table

    // Zero out data members from offset +0x50 to +0x73
    this[0x14] = 0;  // +0x50
    this[0x15] = 0;  // +0x54
    this[0x16] = 0;  // +0x58

    // Zero 4 bytes at offset +0x5C using two 16-bit writes
    *(undefined2 *)(this + 0x17) = 0;          // +0x5C: low word
    *(undefined2 *)((int)this + 0x5e) = 0;     // +0x5E: high word

    this[0x18] = 0;  // +0x60

    // Zero 4 bytes at offset +0x64
    *(undefined2 *)(this + 0x19) = 0;          // +0x64: low word
    *(undefined2 *)((int)this + 0x66) = 0;     // +0x66: high word

    this[0x1a] = 0;  // +0x68

    // Zero 4 bytes at offset +0x6C
    *(undefined2 *)(this + 0x1b) = 0;          // +0x6C: low word
    *(undefined2 *)((int)this + 0x6e) = 0;     // +0x6E: high word

    this[0x1c] = 0;  // +0x70

    return this;
}