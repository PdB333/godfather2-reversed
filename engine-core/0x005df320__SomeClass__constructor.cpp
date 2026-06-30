// FUNC_NAME: SomeClass::constructor
undefined4* __thiscall SomeClass::constructor(undefined4* this, byte cleanupFlag) {
    // Set vtable pointer (offset 0)
    *this = &PTR_FUN_00e3f2d8;
    
    // Call base class constructor (likely initializes base members)
    baseClassConstructor();
    
    // If cleanupFlag bit 0 is set, free the object (e.g., on construction failure)
    if ((cleanupFlag & 1) != 0) {
        operatorDelete(this); // or destructor/cleanup function
    }
    
    return this;
}