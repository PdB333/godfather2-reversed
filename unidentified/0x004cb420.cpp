// 0x004cb420 - Scalar deleting destructor for EARSObject
void* __thiscall EARSObject::scalarDeletingDestructor(byte deallocationFlags) {
    // Call the actual destructor (0x004cb490)
    this->~EARSObject();

    // If the object was heap-allocated (bit 0 set), free its memory via operator delete (0x009c8eb0)
    if (deallocationFlags & 1) {
        operator delete(this);
    }

    return this;
}