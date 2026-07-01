// FUNC_NAME: SomeClass::~SomeClass
// This destructor calls the base destructor (FUN_00906260) and, if the deletion flag
// (param_2) has bit 0 set, frees the object memory using a custom deallocator (FUN_0043b960)
// with the known object size of 0x68 (104 bytes).
void __thiscall SomeClass::~SomeClass(byte deletionFlag) {
    // Call base class destructor
    FUN_00906260();

    // If the object was heap-allocated (deletionFlag & 1), free the memory
    if (deletionFlag & 1) {
        // Custom memory deallocation with size 0x68
        FUN_0043b960(this, 0x68);
    }
}