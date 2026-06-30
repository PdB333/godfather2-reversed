// FUNC_NAME: EARSObject::EARSObject
undefined4* __thiscall EARSObject::EARSObject(undefined4* this, byte constructorFlags) {
    // Set vtable pointer for this class
    *this = &PTR_FUN_00e331b0;
    // Set vtable pointers for base classes at offsets 0x3C (0xF) and 0x48 (0x12)
    this[0xF] = &PTR_LAB_00e331d0;   // +0x3C: base class vtable 1
    this[0x12] = &PTR_LAB_00e331e0; // +0x48: base class vtable 2
    // Construct member object at offset 0x50 (0x14)
    FUN_004086d0(this + 0x14);      // likely constructor for member
    FUN_00408310(this + 0x14);      // likely additional initialization
    // Global initialization (e.g., static counter or pool)
    FUN_0046c640();
    // If allocation flag is set, call a registered destructor/allocator function
    if ((constructorFlags & 1) != 0) {
        // Dereference global pointer at DAT_01223410 + 0x2D4 to get a structure,
        // then call a function at offset 4 within that structure
        (**(code **)(**(int **)(DAT_01223410 + 0x2D4) + 4))(this, 0);
    }
    return this;
}