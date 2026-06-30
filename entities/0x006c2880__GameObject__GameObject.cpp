// FUNC_NAME: GameObject::GameObject
undefined4* __thiscall GameObject::GameObject(undefined4* this, byte flags) {
    // Set primary vtable pointer
    *this = &PTR_FUN_00d5ef08;
    // Set secondary vtable pointers (multiple inheritance)
    // Offsets: +0x3C, +0x48, +0x50
    this[0xf] = &PTR_LAB_00d5eef8;  // +0x3C
    this[0x12] = &PTR_LAB_00d5eef4; // +0x48
    this[0x14] = &PTR_LAB_00d5eef0; // +0x50

    // If sub-object pointer at +0x90 is non-null, destroy it
    if (this[0x24] != 0) {          // +0x90
        FUN_004daf90(this + 0x24);  // destroySubObject
    }
    // Global initialization step
    FUN_00473880();                  // globalInitialize

    // If flag bit 0 is set, delete this object (allocation cleanup)
    if ((flags & 1) != 0) {
        FUN_0043b960(this, 0x1b0);  // operator delete(this, size)
    }
    return this;
}