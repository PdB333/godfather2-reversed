// FUNC_NAME: SimNpc::constructor (at 0x006eae50, calls base constructor FUN_0046c590)
// Reconstructed from Ghidra decompilation. Base class constructor is called, then vtable pointers are set up,
// and a large block of fields (from +0x50 to +0x88) are zeroed.
undefined4* __thiscall SimNpc::constructor(SimNpc* this, undefined4 param_2) {
    // Call base class constructor (likely SimBase or Entity constructor)
    baseConstructor(param_2); // FUN_0046c590
    // Set up vtable pointers for this derived class (multiple inheritance)
    this->vtable = (SimNpcVTable*)&PTR_FUN_00d5fe00; // primary vtable at +0x00
    this->secondaryVtable1 = &PTR_LAB_00d5fdf0;     // secondary vtable at +0x3C (index 0xf)
    this->secondaryVtable2 = &PTR_LAB_00d5fdec;     // third vtable at +0x48 (index 0x12)
    // Initialize fields from +0x50 to +0x88
    this->field_0x50 = 0;                            // +0x50 (int)
    *(uint16*)((uintptr_t)this + 0x54) = 0;          // +0x54 (short)
    *(uint16*)((uintptr_t)this + 0x56) = 0;          // +0x56 (short)
    // Zero four sets of four consecutive ints (likely arrays or members)
    this->field_0x58 = 0;  // +0x58
    this->field_0x5C = 0;  // +0x5C
    this->field_0x60 = 0;  // +0x60
    this->field_0x64 = 0;  // +0x64
    this->field_0x68 = 0;  // +0x68
    this->field_0x6C = 0;  // +0x6C
    this->field_0x70 = 0;  // +0x70
    this->field_0x74 = 0;  // +0x74
    this->field_0x78 = 0;  // +0x78
    this->field_0x7C = 0;  // +0x7C
    this->field_0x80 = 0;  // +0x80
    this->field_0x84 = 0;  // +0x84
    this->field_0x88 = 0;  // +0x88
    return this;
}