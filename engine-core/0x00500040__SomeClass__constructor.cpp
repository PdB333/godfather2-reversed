// FUNC_NAME: SomeClass::constructor
undefined4 __thiscall SomeClass::constructor(SomeClass* this, byte flag) {
    // Call base class constructor or initialization function
    this->baseInit();  // FUN_004ffdf0
    // If the least significant bit of flag is set, call additional initialization
    if ((flag & 1) != 0) {
        this->extraInit();  // FUN_009c8eb0
    }
    return this;
}