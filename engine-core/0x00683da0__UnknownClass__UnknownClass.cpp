// FUNC_NAME: UnknownClass::UnknownClass
undefined4 * __thiscall UnknownClass::UnknownClass(undefined4 *this, byte flags) {
    // Set vtable pointer (offset 0x0)
    *this = &PTR_FUN_00d5885c;
    // Set additional class-specific pointers at offsets 0x3C and 0x48
    this[0xf] = &PTR_LAB_00d5884c;   // +0x3C
    this[0x12] = &PTR_LAB_00d58848;  // +0x48
    // Call base class constructor
    FUN_0046c640();
    // If flag bit 0 is set, call operator delete with size 0x50 (heap allocation)
    if ((flags & 1) != 0) {
        FUN_0043b960(this, 0x50);
    }
    return this;
}