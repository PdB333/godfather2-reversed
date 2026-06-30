// FUNC_NAME: Sentient::Sentient

undefined4 * __thiscall Sentient::Sentient(Sentient *this, undefined4 param_2)
{
    // Call base class constructor (or external initializer) with the given parameter
    FUN_0046c590(param_2);

    // Set virtual function table pointer
    *this = (undefined4 *)&PTR_FUN_00d60bd8; // +0x00: vtable

    // Additional vtable pointers for multiple inheritance (likely base classes)
    this[0xf] = &PTR_LAB_00d60bc8;  // +0x3C
    this[0x12] = &PTR_LAB_00d60bc4; // +0x48

    // Initialize many fields to zero
    this[0x14] = 0; // +0x50

    // 2-byte zero writes at various offsets
    *(uint16 *)((uint8 *)this + 0x54) = 0; // +0x54
    *(uint16 *)((uint8 *)this + 0x56) = 0; // +0x56
    this[0x16] = 0; // +0x58
    *(uint16 *)((uint8 *)this + 0x5C) = 0; // +0x5C
    *(uint16 *)((uint8 *)this + 0x5E) = 0; // +0x5E
    this[0x18] = 0; // +0x60
    this[0x19] = 0; // +0x64
    this[0x1a] = 0; // +0x68
    this[0x1b] = 0; // +0x6C
    *(uint8 *)((uint8 *)this + 0x70) = 0; // +0x70
    this[0x1d] = 0; // +0x74
    this[0x1e] = 0; // +0x78
    this[0x1f] = 0; // +0x7C
    this[0x20] = 0; // +0x80
    this[0x21] = 0; // +0x84
    this[0x22] = 0; // +0x88

    // Debug magic/sentinel values for integrity checking
    this[0x24] = 0xbadbadba; // +0x90
    this[0x25] = 0xbeefbeef; // +0x94
    this[0x26] = 0xeac15a55; // +0x98
    this[0x27] = 0x91100911; // +0x9C

    return this;
}