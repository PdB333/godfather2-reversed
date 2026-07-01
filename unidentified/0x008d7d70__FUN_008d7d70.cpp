// FUNC_NAME: SomeClass::scalarDeletingDestructor
// Address: 0x008d7d70
// Role: Scalar deleting destructor wrapper.
// Calls the actual destructor (at 0x008d7b20) and optionally frees memory (at 0x009c8eb0).
// Replace SomeClass with the actual class name when known.

void __thiscall SomeClass::scalarDeletingDestructor(byte flags) {
    // Invoke the destructor proper (separate function)
    this->~SomeClass();
    // If the low bit of flags is set, deallocate the object's memory
    if (flags & 1) {
        // FUN_009c8eb0 likely corresponds to operator delete or a custom deallocator
        operator delete(this);
    }
}