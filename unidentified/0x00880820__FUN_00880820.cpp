// FUNC_NAME: SomeClass::SomeClass
// Reconstructed constructor for a class derived from BaseClass.
// At offset +0x0 is the vtable pointer.

void* __thiscall SomeClass::SomeClass(byte flags) {
    // Set vtable to base class (offset +0x0)
    *(void**)this = &baseClassVtable;   // PTR_FUN_00d76bc0
    // Call base class constructor
    BaseClass::BaseClass(this);         // FUN_0043e380
    // Set vtable to derived class (offset +0x0)
    *(void**)this = &derivedClassVtable; // PTR_LAB_00e30ea0
    // If bit 0 of flags is set, call deallocation routine
    if (flags & 1) {
        deallocateMemory(this);         // FUN_009c8eb0
    }
    return this;
}