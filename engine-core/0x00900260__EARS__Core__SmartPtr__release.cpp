// FUNC_NAME: EARS::Core::SmartPtr::release
void __cdecl SmartPtr::release(SmartPtr* smartPtr, RefCountedObject* owner) {
    // Stack-allocated vtable pointer for reference counting stub
    void* stubVtable[1];  // local_18
    int stubPtr;          // local_14 (address of embedded stub at owner+0x48)
    int savedField;       // local_10 (previous value at owner+0x4c)
    int smartPtrBackup;   // local_c copy of smart pointer value
    bool dummy;           // local_4

    void* vtableAddrHolder = (void**)&stubVtable;  // local_8

    if (owner == nullptr) {
        // No owner – just decrement reference count of the smart pointer
        smartPtrBackup = smartPtr->rawPtr;  // assume first field is raw pointer
        vtableAddrHolder = nullptr;
        dummy = false;
        decRefCount(&smartPtrBackup, 0);  // FUN_00408a00
    } else {
        // Owner object has a reference count stub embedded at offset +0x48
        stubPtr = reinterpret_cast<int>(owner) + 0x48;

        // Set up a local vtable for the stub (the stub's destructor entry)
        stubVtable[0] = reinterpret_cast<void*>(&PTR_FUN_00e31e2c);  // global function pointer
        savedField = 0;

        if (stubPtr != 0) {
            // Save the old stub pointer field (owner+0x4c) and replace it
            // with a pointer to the stack-allocated stub variable
            savedField = *(int*)(reinterpret_cast<char*>(owner) + 0x4c);
            *(int**)(reinterpret_cast<char*>(owner) + 0x4c) = &stubPtr;
        }

        // Decrement reference count of the smart pointer
        smartPtrBackup = smartPtr->rawPtr;
        dummy = false;
        decRefCount(&smartPtrBackup, 0);

        // If the stub still exists after release, free it
        if (stubPtr != 0) {
            freeStubBlock(&stubPtr);  // FUN_004daf90
        }
    }
}