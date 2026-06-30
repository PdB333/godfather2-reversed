// FUNC_NAME: UnknownClass::scalarDeletingDestructor

// 0x00418720: Scalar deleting destructor for an UnknownClass instance.
// Calls the actual destructor (0x00418740) and, if deleteFlag's LSB is set,
// deallocates the memory via operator delete (0x009c8eb0).
// Returns the this pointer (standard for MSVC scalar deleting destructors).

void* __thiscall UnknownClass::scalarDeletingDestructor(void* this, int deleteFlag) {
    // Call the actual destructor (FUN_00418740) – virtual destructor dispatcher or inline
    this->~UnknownClass();          // Equivalent to call at 0x00418740

    // If deleteFlag LSB is 1, deallocate the object
    if (deleteFlag & 1) {
        operator delete(this);      // Equivalent to call at 0x009c8eb0
    }

    return this;                    // Return 'this' for call chaining
}