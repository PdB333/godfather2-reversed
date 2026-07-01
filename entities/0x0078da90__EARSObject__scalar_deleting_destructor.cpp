// FUNC_NAME: EARSObject::scalar_deleting_destructor
// Address: 0x0078da90
// Role: Compiler-generated "scalar deleting destructor" for EARSObject.
// Calls the actual destructor if the object is valid (vtable pointer non-null),
// then frees memory if the deallocation flag is set.

int* __thiscall EARSObject::scalarDeletingDestructor(int* this_, byte deallocFlag)
{
    // +0x00: vtable pointer (non-null indicates a valid constructed object)
    if (*this_ != 0)
    {
        // Call the actual destructor (cleanup logic)
        EARSObject::destroy(this_);
    }
    if ((deallocFlag & 1) != 0)
    {
        // Free the memory allocated for this object
        EARSObject::operatorDelete(this_);
    }
    return this_;
}