// FUNC_NAME: SomeClass::create
SomeClass* __thiscall SomeClass::create(SomeClass* this, byte flag) {
    // Call base class constructor
    baseConstructor(this); // FUN_00768c20
    // If flag bit 0 is set, perform additional initialization
    if (flag & 1) {
        additionalInit(this); // FUN_00624da0
    }
    return this;
}