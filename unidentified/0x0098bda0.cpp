// FUN_0098bda0: SomeClass::destructor (object cleanup with callback and optional deallocation)
// This function resembles a destructor that optionally invokes a member function pointer
// then conditionally deletes the object based on a flag.
// Offsets:
//   +0x14: pointer to a sub-object (likely dynamically allocated)
//   +0x20: function pointer for destroying the sub-object (e.g., virtual destructor thunk)
int __thiscall SomeClass::destructor(SomeClass *this, byte flags) {
    if (this->field_0x14 != 0) {
        // Call the destructor or cleanup routine stored at offset 0x20
        (*(void (__thiscall *)(int))(this->field_0x20))(this->field_0x14);
    }
    // If the lower bit of flags is set, deallocate the memory for this object.
    if ((flags & 1) != 0) {
        FUN_009c8eb0(this);  // Likely operator delete or a custom deallocator
    }
    return this;  // Standard for destructors returning this pointer in some compilers
}