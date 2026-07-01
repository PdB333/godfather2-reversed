// FUNC_NAME: SomeClass::constructorWithOptionalDeallocation
undefined4 __thiscall SomeClass::constructor(SomeClass* this, byte flags) {
    // Call base class constructor or initialization routine
    // FUN_009068c0 is a static function that initializes base members
    SomeClass::baseInitialization();

    // If the low bit of flags is set, perform a custom deallocation
    // This likely indicates that the object was dynamically allocated and
    // should be freed after construction (purpose unclear – possibly a factory pattern)
    if ((flags & 1) != 0) {
        operatorDelete(this, 0x68); // FUN_0043b960 – Operator delete with size 0x68
    }

    return (undefined4)this;
}