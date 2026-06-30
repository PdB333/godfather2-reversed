// FUNC_NAME: RefCountedObject::release
// Address: 0x004e89e0
// This function appears to decrement the reference count of a ref-counted object.
// It checks the object's validity via a virtual function (vtable+0x8) before decrementing.
// Returns a boolean-like pointer: non-null if the check passed, null otherwise.
// The refcount is at offset +0x04, vtable at +0x00.

bool* __fastcall RefCountedObject::release(void* context, void* param_2, int* objectPtr) {
    // local_4 is an int initialized to 0, but the function returns a pointer to it as a boolean indicator.
    // The actual function may return a bool, but the decompiler shows returning address of a local.
    // We'll simulate by returning a pointer to a static or a variable.
    // For clarity, we treat the return as a boolean and use a dummy stack variable.
    bool* result;
    int* refCountPtr;
    char validityCheck;
    
    result = nullptr; // equivalent to returning 0

    if (objectPtr != nullptr) {
        // Call virtual function at vtable offset +0x8 (likely bool isValid(void* context))
        validityCheck = (*(code**)(*objectPtr + 0x8))(param_2);
        if (validityCheck != 0) {
            // Object passed validity check
            refCountPtr = objectPtr + 1; // +0x04 = reference count
            (*refCountPtr)--;
            if (*refCountPtr == 0) {
                // Call destructor via vtable at +0x4
                (*(code**)(*objectPtr + 0x4))();
            }
            return reinterpret_cast<bool*>(&result); // dummy non-null pointer
        } else {
            // Validity check failed, still decrement refcount
            refCountPtr = objectPtr + 1;
            (*refCountPtr)--;
            if (*refCountPtr == 0) {
                (*(code**)(*objectPtr + 0x4))();
            }
            return nullptr; // failure
        }
    }
    return nullptr;
}