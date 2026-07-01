// FUNC_NAME: SomeClass::SomeClass
// Address: 0x0083fec0
// Role: Constructor for a class with vtable and two additional function pointers at offsets 0x3C (0xF*4) and 0x48 (0x12*4). Calls base constructor FUN_0083f920. If param_2 & 1 is set, calls operator delete with size 0x5C (92 bytes) – likely a placement delete for self-allocation.

SomeClass* __thiscall SomeClass::SomeClass(SomeClass* this, byte flags) {
    // Set vtable pointer (offset +0x00)
    this->vtable = &PTR_FUN_00d7452c;
    // Set function pointer at offset +0x3C (0xF * 4)
    this->field_0x3C = &PTR_LAB_00d7451c;
    // Set function pointer at offset +0x48 (0x12 * 4)
    this->field_0x48 = &PTR_LAB_00d74518;
    // Call base class constructor
    FUN_0083f920();
    // If the low bit of flags is set, deallocate this object (size 0x5C)
    if ((flags & 1) != 0) {
        FUN_0043b960(this, 0x5c);
    }
    return this;
}