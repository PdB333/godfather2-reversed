// FUNC_NAME: EARSObject::EARSObject
undefined4 * __thiscall EARSObject::EARSObject(undefined4 *this, byte flags) {
    // Set vtable pointers for the current class and possibly parent interfaces.
    // Offsets are in dword multiples: 0xf -> +0x3C, 0x12 -> +0x48, 0x14 -> +0x50
    *this = &PTR_FUN_00e32af4;                                       // +0x00 (main vtable)
    this[0xf] = &PTR_LAB_00e32b18;                                   // +0x3C (likely interface vtable)
    this[0x12] = &PTR_LAB_00e32b28;                                  // +0x48
    this[0x14] = &PTR_LAB_00e32b2c;                                  // +0x50 (first assignment)
    this[0x14] = &PTR_LAB_00e32854;                                  // +0x50 (overwritten – maybe derived class vtable)

    // Call base class initialization or some common setup routine.
    // FUN_0046c640 is likely a base constructor or a static initializer.
    FUN_0046c640();

    // If the low bit of flags is set, invoke a finalization/registration callback.
    // DAT_01223410 is a global engine/manager pointer.
    // Offset 0x2d4 points to a vtable-like structure; offset 4 in that vtable is a function.
    if ((flags & 1) != 0) {
        (**(code **)(**(int **)(DAT_01223410 + 0x2d4) + 4))(this, 0);
    }

    return this;
}