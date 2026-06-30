// FUNC_NAME: BaseComponent::BaseComponent
// Address: 0x006a73c0
uint* __thiscall BaseComponent::BaseComponent(uint* this, uint param) {
    // Call unidentified base initializer or setup function
    sub_46c590(param);

    // Set up vtable pointer at offset 0x00
    this[0] = &PTR_FUN_00d5d840;   // +0x00: vtable

    // Set up additional function pointer tables
    this[0x0F] = &PTR_LAB_00d5d830; // +0x3C: function table 1?
    this[0x12] = &PTR_LAB_00d5d82c; // +0x48: function table 2?

    // Zero out fields from offset 0x50 to 0x8C
    this[0x14] = 0;  // +0x50
    this[0x1c] = 0;  // +0x70
    this[0x14] = 0;  // duplicate, but kept as decompiled
    this[0x1d] = 0;  // +0x74
    this[0x15] = 0;  // +0x54
    this[0x1e] = 0;  // +0x78
    this[0x16] = 0;  // +0x58
    this[0x1f] = 0;  // +0x7C
    this[0x17] = 0;  // +0x5C
    this[0x20] = 0;  // +0x80
    this[0x18] = 0;  // +0x60
    this[0x21] = 0;  // +0x84
    this[0x19] = 0;  // +0x64
    this[0x22] = 0;  // +0x88
    this[0x1a] = 0;  // +0x68
    this[0x23] = 0;  // +0x8C
    this[0x1b] = 0;  // +0x6C

    return this;
}