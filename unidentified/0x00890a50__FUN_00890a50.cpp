// FUNC_NAME: SomeClass::scalarDeletingDestructor
// Address: 0x00890a50 - Scalar deleting destructor for a class of size 0x1E0 (480 bytes)
// Pattern: MSVC-style deleting destructor - calls base destructor, then optionally deletes memory.
void* __thiscall SomeClass::scalarDeletingDestructor(byte deletingFlag) {
    // Call the base destructor (actual cleanup logic)
    this->destructorImpl();  // Calls FUN_00890660 (the actual destructor)

    // If bit 0 of flag is set, call operator delete with the class size
    if (deletingFlag & 1) {
        operatorDelete(this, 0x1E0);  // Calls FUN_0043b960 (scalar delete with size)
    }

    return this;  // Return pointer to object (common for deleters)
}