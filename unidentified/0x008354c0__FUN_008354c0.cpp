//FUNC_NAME: SomeClass::SomeClass
// Address: 0x008354c0
// Role: Constructor for SomeClass, calls base constructor and optionally performs additional initialization based on flags.

SomeClass* __thiscall SomeClass::SomeClass(SomeClass* this, byte flags) {
    // Call base class constructor (FUN_00835120)
    BaseClass::BaseClass(this);

    // If the lowest bit of flags is set, call additional initialization/registration (FUN_009c8eb0)
    if ((flags & 1) != 0) {
        SomeClass::additionalInit(this);
    }

    return this;
}