// FUNC_NAME: NPC::NPC
undefined4 * __thiscall NPC::NPC(undefined4 *this, undefined4 creationData)
{
    // Call base class constructor (likely Entity or Sentient)
    FUN_0046c590(creationData);

    // Initialize vtable pointers for multiple inheritance
    *this = &PTR_FUN_00d74c84;          // Main vtable at offset 0
    this[0xf] = &PTR_LAB_00d74c74;      // Secondary vtable at offset 0x3C
    this[0x12] = &PTR_LAB_00d74c70;     // Tertiary vtable at offset 0x48

    // Zero out various fields
    this[0x14] = 0;                     // offset 0x50 (int or pointer)
    this[0x15] = 0;                     // offset 0x54 (int or pointer)
    *(undefined2 *)((int)this + 0x58) = 0;  // short at +0x58
    *(undefined2 *)((int)this + 0x5A) = 0;  // short at +0x5A
    this[0x17] = 0;                     // offset 0x5C (int or pointer)

    return this;
}