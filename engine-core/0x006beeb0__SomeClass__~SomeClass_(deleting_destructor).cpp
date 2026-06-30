// FUNC_NAME: SomeClass::~SomeClass (deleting destructor)
undefined4 __thiscall SomeClass::~SomeClass(byte destroyingFlag) {
    // Call the actual destructor logic (member cleanup)
    SomeClass::vdestructor(); // FUN_006bea60
    
    // If the high bit of the flag is set, deallocate the memory
    if ((destroyingFlag & 1) != 0) {
        // Custom deallocation: likely operator delete(this) or a specialized deallocator
        SomeClass::operatorDelete(this); // FUN_009c8eb0
    }
    
    return this;
}