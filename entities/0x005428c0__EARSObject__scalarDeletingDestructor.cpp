// FUNC_NAME: EARSObject::scalarDeletingDestructor
// Address: 0x005428c0
// Role: Deleting destructor for an EARS framework object. Calls base destructor (FUN_00542920) and conditionally deallocates memory if flag & 1.
int __thiscall EARSObject::scalarDeletingDestructor(EARSObject* this, unsigned char flag) {
    // Call base class destructor (likely EARSObject or a base in hierarchy)
    this->~EARSObject(); // FUN_00542920

    // If flag indicates deletion (bit 0 set), invoke deallocation via vtable
    if (flag & 1) {
        // DAT_01223410 + 0x2d4 holds a pointer to a vtable table or function pointer array
        // +4 is the second entry (offset 4 bytes) – typically operator delete or custom deallocator
        void (*deallocate)(void*, int) = (void (*)(void*, int))(
            *(int*)(*(int*)(DAT_01223410 + 0x2d4) + 4)
        );
        deallocate(this, 0);
    }

    // Return the object pointer (standard for __thiscall destructor returning this)
    return (int)this;
}