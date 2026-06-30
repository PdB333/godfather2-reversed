// FUNC_NAME: UnknownClass::`scalar deleting destructor'
void* __thiscall UnknownClass::scalarDeletingDestructor(void* this, byte deletingFlag) {
    // Call the base destructor (likely a virtual or non-virtual destructor)
    this->~UnknownClass(); // Represents FUN_00741f40

    // If the low bit of the flag is set, deallocate the memory
    if (deletingFlag & 1) {
        // operator delete to free the object storage
        operator delete(this); // Represents FUN_00624da0
    }

    // Return the original pointer (may be used for chaining or ABI)
    return this;
}