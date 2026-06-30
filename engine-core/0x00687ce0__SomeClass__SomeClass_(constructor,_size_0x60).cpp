// FUNC_NAME: SomeClass::SomeClass (constructor, size 0x60)
undefined4 __thiscall SomeClass::SomeClass(undefined4 this, byte flags) {
    // Call base class or initialization function (likely EARSObject base constructor)
    FUN_0090e420();
    // If the low bit of flags is set, deallocate memory (failure path or cleanup)
    if ((flags & 1) != 0) {
        FUN_0043b960(this, 0x60); // operator delete or custom dealloc (size=0x60)
    }
    return this;
}