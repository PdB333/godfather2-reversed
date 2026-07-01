// FUNC_NAME: SomeClass::SomeClass

SomeClass* __thiscall SomeClass::SomeClass(SomeClass* this, byte flags) {
    // Call base class constructor (FUN_007b0030)
    this->BaseClass::BaseClass();

    // If the least significant bit of flags is set, perform additional initialization
    // (FUN_00624da0 is likely a derived-class-specific initializer)
    if (flags & 1) {
        this->initAdditional(this);
    }

    return this;
}