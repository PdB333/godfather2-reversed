// FUNC_NAME: EARSObject::scalarDeletingDestructor

void __thiscall EARSObject::scalarDeletingDestructor(EARSObject* this) {
    // Common scalar deleting destructor pattern:
    // 1. Call the actual virtual destructor (or final destructor chain)
    // 2. Deallocate the memory block with a global deallocation function
    // The second argument (4) is likely a type identifier or small size hint
    if (this != nullptr) {
        // Call the destructor implementation (likely virtual destructor entry point)
        EARSObject::destructor(); // FUN_005b1e40

        // Deallocate memory via global function pointer (operator delete or custom allocator)
        // DAT_0119caf8 is a global pointer to the deallocation routine
        // The constant 4 might indicate size class, allocation flag, or alignment
        (*DAT_0119caf8)(this, 4);
    }
}