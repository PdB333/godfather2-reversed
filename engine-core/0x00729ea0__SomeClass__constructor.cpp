// FUNC_NAME: SomeClass::constructor
undefined4* __thiscall SomeClass::constructor(SomeClass* this, byte allocateFlag) {
    // Set vtable to class's main vtable
    this->vtable = &gVtable_SomeClass; // PTR_FUN_00d62544

    // Set secondary vtable pointers at offsets 0x3C and 0x48 (for multiple inheritance)
    this->secondaryVtable1 = &gVtable_SomeClass_Secondary1; // PTR_LAB_00d62534
    this->secondaryVtable2 = &gVtable_SomeClass_Secondary2; // PTR_LAB_00d62530

    // Call base class constructor (likely at offset 0 of this)
    FUN_00728f70(this); // BaseClass::constructor

    // Global initialization (e.g., module setup)
    FUN_0046c640();

    // If the low bit of allocateFlag is set, this object was heap-allocated,
    // so we must associate it with the allocator. (Possibly a placement new callback)
    if ((allocateFlag & 1) != 0) {
        // FUN_0043b960 takes a pointer and size (0x78 = 120 bytes, the class size)
        // This might be a call to register the allocation or mark it for proper deletion.
        FUN_0043b960(this, 0x78); // Allocator::registerObject(this, size)
    }

    return this;
}