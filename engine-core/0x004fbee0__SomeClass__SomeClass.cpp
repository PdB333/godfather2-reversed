// FUNC_NAME: SomeClass::SomeClass
undefined4 __thiscall SomeClass::SomeClass(SomeClass *this, byte initFlags) {
    // Call base class initializer
    FUN_004fa0b0();
    // If flag bit 0 is set, call cleanup/shutdown function
    if ((initFlags & 1) != 0) {
        FUN_009c8eb0(this);
    }
    return (undefined4)this;
}