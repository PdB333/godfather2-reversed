// FUNC_NAME: EARSBaseObject::scalarDeletingDestructor
// Address: 0x005bd290
// Role: Deleting destructor wrapper. Calls internal destructor (body at 0x005bd2c0)
//       and optionally deallocates memory via operator delete if flag bit 0 is set.

void * __thiscall EARSBaseObject::scalarDeletingDestructor(int flags) {
    // Call the actual destructor logic (presumably a member function)
    this->destructorBody();
    // If the deletion flag (bit 0) is set, free the memory
    if (flags & 1) {
        ::operator delete(this);  // Calls custom deallocator at 0x009c8eb0
    }
    return this;
}