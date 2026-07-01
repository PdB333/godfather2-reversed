// FUNC_NAME: SomeClass_00795160::constructor (vtable at 0x00d6a0c8, baseInit at 0x004149b0, cleanup at 0x009c8eb0)
undefined4* __thiscall SomeClass_00795160::constructor(SomeClass_00795160* this, byte cleanupFlag) {
    this->vtable = &PTR_FUN_00d6a0c8; // Set vtable pointer for this class
    BaseClassInit(); // Call base class initialization (likely EARSObject or similar)
    if (cleanupFlag & 1) {
        DestroyObject(this); // If cleanupFlag bit 0 set, call object destructor/cleanup
    }
    return this;
}