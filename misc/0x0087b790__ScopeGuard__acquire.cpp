// FUNC_NAME: ScopeGuard::acquire
void __thiscall ScopeGuard::acquire(void* this) {
    // Local guard structure on stack: vtable pointer, managed object, previous guard, global current, etc.
    void* guardVtable = &PTR_FUN_00d76670; // vtable for guard object
    void* managedObject = nullptr;          // +0x04 in guard structure? (local_14)
    void* previousGuard = nullptr;          // saved from this+0x4c (local_10)
    int globalCurrent = DAT_0112ada8;       // global variable holding current guard
    void* guardStruct = &managedObject;     // pointer to beginning of guard structure (local_8)
    char guardFlag = 0;                     // used as terminator (local_4)

    if (this != nullptr && (this + 0x48) != nullptr) {
        // Save previous guard pointer from object at offset 0x4c
        previousGuard = *(void**)(this + 0x4c);
        // Replace object's guard pointer with address of the stack guard's managedObject field
        *(void***)(this + 0x4c) = &managedObject;
        // Set managedObject to point to offset 0x48 of the object (likely the data being guarded)
        managedObject = this + 0x48;
    }

    // Call a function with the global current guard and zero (push onto stack?)
    FUN_00408a00(&globalCurrent, 0);

    // If a managed object was set, call cleanup function (pop from stack?)
    if (managedObject != nullptr) {
        FUN_004daf90(&managedObject);
    }

    return;
}