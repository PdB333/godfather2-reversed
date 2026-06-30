// FUNC_NAME: RefCountedPtr::operator=
void __thiscall RefCountedPtr::operator=(void* newPtr)
{
    // This is a smart pointer assignment operator for reference-counted objects.
    // The class holds a single raw pointer m_ptr at offset 0 from this.
    // m_ptr points to a polymorphic object with layout:
    //   +0x00: vtable pointer (4 bytes)
    //   +0x04: some field? (4 bytes, not used here)
    //   +0x08: reference count (int)
    // The vtable at index 2 (offset 0x08 from vtable start) is assumed to be the destructor.

    void* oldPtr = *(void**)this; // dereference this to get the old pointer (since this points to the m_ptr member)
    if (oldPtr != nullptr)
    {
        int* refCountPtr = (int*)oldPtr + 2; // offset +0x08 (each int is 4 bytes)
        *refCountPtr = *refCountPtr - 1;     // decrement reference count
        if (*refCountPtr == 0)
        {
            // Call virtual destructor via vtable at offset 0x08
            void (**vtable)(void) = *(void (***)(void))oldPtr;
            vtable[2](); // third virtual function (destructor)
        }
    }

    // Store the new pointer
    *(void**)this = newPtr;

    if (newPtr != nullptr)
    {
        int* refCountPtr = (int*)newPtr + 2; // offset +0x08
        *refCountPtr = *refCountPtr + 1;     // increment reference count
    }
}