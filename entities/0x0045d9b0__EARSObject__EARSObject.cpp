// FUNC_NAME: EARSObject::EARSObject

// 0045d9b0 - Constructor for a base EARS object, calls base initialization and optionally sets up vtable or calls a virtual initializer.
void* __thiscall EARSObject::EARSObject(void* thisPtr, uint8_t constructorFlags)
{
    // Call base class or shared initialization routine.
    FUN_0045db70();

    // If the low bit of constructorFlags is set, call an initialization function
    // obtained from a global engine structure at offset 0x2d4 (likely a vtable or factory table).
    // The function at index 4 is invoked with (thisPtr, 0).
    if ((constructorFlags & 1) != 0)
    {
        // DAT_01223410 points to some global engine context; +0x2d4 leads to a pointer,
        // then +4 is a function pointer in an array.
        void** engineContext = *(void***)(DAT_01223410 + 0x2d4);
        void (*initFunc)(void*, int) = (void (*)(void*, int))engineContext[1]; // index 4? Actually +4 bytes from start means second element if pointers are 4 bytes.
        // The decompiled code uses +4 offset, which for a 32-bit pointer array is the second element (index 1).
        initFunc(thisPtr, 0);
    }
    return thisPtr;
}