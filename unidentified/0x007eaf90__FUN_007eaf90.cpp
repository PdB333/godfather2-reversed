// FUNC_NAME: SomeClass::scalarDeletingDestructor
// Function address: 0x007eaf90
// Role: Scalar deleting destructor wrapper (MSVC pattern)
// Calls the real destructor (0x007eacd0) and optionally frees memory via operator delete (0x00624da0)
int __thiscall SomeClass::scalarDeletingDestructor(byte flags) {
    // Call the destructor at 0x007eacd0
    this->~SomeClass();

    // If the low bit of flags is set, free the memory
    if (flags & 1) {
        ::operator delete(this); // operator delete at 0x00624da0
    }

    // Return the this pointer (common in some compiler-generated thunks)
    return reinterpret_cast<int>(this);
}