// FUNC_NAME: EARSObject::scalarDeletingDestructor
// 0x005667a0: Scalar deleting destructor wrapper for EARSObject.
// Calls real destructor (0x005667d0), then optionally frees memory (operator delete at 0x009c8eb0).
void* __thiscall EARSObject::scalarDeletingDestructor(byte deletingFlag) {
    // Invoke the actual destructor (found at 0x005667d0)
    this->~EARSObject();
    // If the low bit of the flag is set, free the object's memory block
    if (deletingFlag & 1) {
        operator delete(this);
    }
    return this;
}