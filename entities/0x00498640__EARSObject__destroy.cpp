// FUNC_NAME: EARSObject::destroy
// Address: 0x00498640
// This function releases two internal buffers (at offsets +0x04 and +0x10) and optionally frees the object itself.
// The flag parameter controls whether the object's memory is deallocated (bit 0).
int __thiscall EARSObject::destroy(byte flags) {
    // Free the buffer referenced at +0x10
    freeMemory(*(void**)(this + 0x10));
    // Free the buffer referenced at +0x04 if non-null
    if (*(int*)(this + 4) != 0) {
        freeMemory(*(void**)(this + 4));
    }
    // If bit 0 of flags is set, deallocate the object itself
    if ((flags & 1) != 0) {
        freeObject(this);
    }
    return (int)this;
}