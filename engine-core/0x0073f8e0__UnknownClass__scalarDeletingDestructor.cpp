// FUNC_NAME: UnknownClass::scalarDeletingDestructor
void* __thiscall UnknownClass::scalarDeletingDestructor(void* this, uint32_t flags) {
    // Call the actual destructor (FUN_0073f2e0)
    this->~UnknownClass(); // or: ((void(__thiscall*)(void*))this->vtable->destructor)(this);
    // If the least significant bit of flags is set, free the memory
    if ((flags & 1) != 0) {
        ::operator delete(this); // FUN_00624da0
    }
    return this;
}