// FUNC_NAME: RefCountedObject::Destroy
int* __thiscall RefCountedObject::Destroy(byte flags) {
    // Call object-specific cleanup if the reference count or identifier is non-zero.
    if (*this != 0) {
        // The cleanup function pointer is stored at offset +0x0C (third int).
        ((void (*)(int))this[3])(*this);
    }
    // If flag bit 0 is set, deallocate the memory.
    if ((flags & 1) != 0) {
        // operator delete or custom deallocation.
        operatorDelete(this);
    }
    return this;
}