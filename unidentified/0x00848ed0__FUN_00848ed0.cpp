//FUNC_NAME: SomeClass::SomeClass

undefined4* __thiscall SomeClass::SomeClass(undefined4* this, byte flags)
{
    // Set primary vtable pointer at offset 0x00
    this[0] = &PTR_FUN_00d74c84;
    // Set secondary vtable pointer at offset 0x3C (0xF * 4)
    this[0xF] = &PTR_LAB_00d74c74;
    // Set tertiary vtable pointer at offset 0x48 (0x12 * 4)
    this[0x12] = &PTR_LAB_00d74c70;

    // Initialize sub-object at offset 0x54 (0x15 * 4)
    FUN_004086d0(this + 0x15);
    FUN_00408310(this + 0x15);

    // Global initialization routine
    FUN_0046c640();

    // If the object was heap-allocated (flags & 1), free it? (unusual in constructor)
    if ((flags & 1) != 0) {
        FUN_0043b960(this, 0x60);
    }

    return this;
}