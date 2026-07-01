// FUNC_NAME: Container::scalarDeletingDestructor
// Address: 0x00792450
// Role: Scalar deleting destructor for a class that owns a pointer member at offset +0x04.
// If the pointer is non-null, it is destroyed via FUN_009c8f10 (likely destructor or release).
// If param_2 has bit 0 set (flags & 1), the object itself is freed via FUN_009c8eb0 (operator delete).
int __thiscall Container::scalarDeletingDestructor(Container* this, unsigned char flags) {
    // Destroy the pointed-to object at offset +0x04
    if (this->m_child != nullptr) { // +0x04 : pointer to sub-object or resource
        FUN_009c8f10(this->m_child); // destructor or release function for the child
    }
    // If delete flag is set, free this object's memory
    if ((flags & 1) != 0) {
        FUN_009c8eb0(this); // operator delete
    }
    return (int)this;
}