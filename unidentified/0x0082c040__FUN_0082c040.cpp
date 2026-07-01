// FUNC_NAME: SomeClass::SomeClass (constructor with flag)
undefined4 __thiscall SomeClass::SomeClass(byte flag) {
    baseInit();                               // call to FUN_0082b7a0 (likely base class constructor/initialization)
    if (flag & 1) {
        optionalInit(this);                   // call to FUN_009c8eb0 (optional initialization/cleanup)
    }
    return this;                              // return this pointer
}