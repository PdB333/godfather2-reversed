// FUNC_NAME: RefCounted::release
int* __thiscall RefCounted::release(int* thisPtr, byte flags)
{
    // If the internal resource pointer (offset 0x00) is non-null, call its release function
    // The release function pointer is stored at offset 0x0C in this object
    if (*thisPtr != 0) {
        ((void (*)(int*))thisPtr[3])(*thisPtr);
    }
    // If the low bit of flags is set, deallocate this RefCounted object itself
    if ((flags & 1) != 0) {
        operator delete(thisPtr);
    }
    return thisPtr;
}