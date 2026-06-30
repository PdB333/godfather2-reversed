// FUNC_NAME: SomeClass::constructorWithFlag
SomeClass* __thiscall SomeClass::constructorWithFlag(SomeClass* this, byte flags) {
    // Call base constructor (FUN_00621290)
    this->baseConstructor();
    // If the lowest bit of flags is set, call a cleanup/destructor-like function (FUN_009c8eb0)
    if (flags & 1) {
        this->conditionalCleanup();
    }
    return this;
}