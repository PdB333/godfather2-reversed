// FUNC_NAME: EARSObject::destroy
// Address: 0x0098dfd0
// Role: Destructor wrapper that calls virtual destructor and optionally deallocates memory.
// The object's vtable pointer is at offset 0x00, and the destructor function pointer is at offset 0x0C.
// param_2: bit 0 set indicates memory should be freed via EARS::Memory::deallocate.

int* __thiscall EARSObject::destroy(int* thisPtr, byte flags)
{
    // If the vtable pointer is non-null, call the virtual destructor
    if (*thisPtr != 0) {
        // The destructor function is stored at offset 0x0C in the vtable
        (*(code (*)(int*))thisPtr[3])(thisPtr);
    }
    // If the low bit of flags is set, free the memory
    if ((flags & 1) != 0) {
        EARS::Memory::deallocate(thisPtr);
    }
    return thisPtr;
}