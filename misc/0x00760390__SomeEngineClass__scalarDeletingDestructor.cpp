// FUNC_NAME: SomeEngineClass::scalarDeletingDestructor
undefined4 * __thiscall SomeEngineClass::scalarDeletingDestructor(byte deletingFlag) {
    // Set vtable to this class's vtable (address from symbol PTR_FUN_00d65404)
    this->vtable = &PTR_FUN_00d65404; // vtable for SomeEngineClass
    // Destroy member pointer at offset +0x04 (if non-null)
    if (this->m_pointer != 0) {
        // Call a function that releases the object pointed to by m_pointer,
        // passing the address of the pointer so it can be cleared.
        // FUN_004daf90 is likely a "release" or "destroy" helper.
        FUN_004daf90(&this->m_pointer); // destroys member object and sets pointer to 0? (not shown)
    }
    // After destruction, set vtable to purecall to prevent accidental calls
    this->vtable = &PTR___purecall_00e407a4;
    // If deletingFlag bit 0 is set, deallocate the memory (operator delete)
    if ((deletingFlag & 1) != 0) {
        FUN_009c8eb0(this); // likely operator delete
    }
    return this;
}