// FUNC_NAME: Object::release
void __fastcall Object::release(uint32_t* thisPtr)
{
    // Assumed structure layout (offsets in bytes):
    // +0x00: pointer to primary object (likely itself or a component)
    // +0x0C: pointer to secondary object (child or sub-object)
    // +0x10: pointer to vtable pointer (indirection to actual vtable)
    //
    // The vtable pointer is stored indirectly: the value at +0x10 is
    // a pointer to the real vtable pointer.
    uint32_t** vtableIndirect = (uint32_t**)thisPtr[4];  // +0x10
    uint32_t* vtable = *vtableIndirect;                  // actual vtable address

    // Define function pointer types for vtable entries.
    // Entry +4 (second slot) is a release function that takes (void* , int)
    typedef void (__fastcall* ReleaseFunc)(void*, int);
    // Entry +0xC (fourth slot) is a destructor/cleanup with no params
    typedef void (__fastcall* DestructorFunc)();

    // Release primary object (first field)
    ((ReleaseFunc)(vtable[1]))((void*)thisPtr[0], 0);

    // If secondary object exists, release it with same function
    if (thisPtr[3] != 0) {
        ((ReleaseFunc)(vtable[1]))((void*)thisPtr[3], 0);
    }

    // Final destructor call (vtable entry +0xC)
    ((DestructorFunc)(vtable[3]))();
}