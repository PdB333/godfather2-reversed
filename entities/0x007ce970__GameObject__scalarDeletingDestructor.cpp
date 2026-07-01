// FUNC_NAME: GameObject::scalarDeletingDestructor
// Address: 0x007ce970
// Role: Scalar deleting destructor wrapper. Calls the real destructor (0x007cdf50) and optionally frees memory via operator delete (0x00624da0) when param_2 & 1 is set.
void* __thiscall GameObject::scalarDeletingDestructor(byte flags) {
    // Call the actual destructor (0x007cdf50)
    this->~GameObject();

    // If the flags indicate the object was heap-allocated, free its memory
    if (flags & 1) {
        // Operator delete (0x00624da0)
        FUN_00624da0(this);
    }

    // Return this pointer (common in MSVC deleting destructors)
    return this;
}