// FUNC_NAME: EARSObject::constructor
undefined4 __thiscall EARSObject::constructor(EARSObject* this, byte flags) {
    // Call base class initializer (likely EARSObject base constructor)
    EARSObject::baseConstructor(this); // FUN_0066d7f0

    // If bit 0 of flags is set, release memory (placement delete / cleanup)
    // This pattern is used by placement new when construction fails or for deferred delete.
    if (flags & 1) {
        EARSObject::deallocate(this); // FUN_009c8eb0 - likely operator delete or custom dealloc
    }

    return reinterpret_cast<undefined4>(this);
}