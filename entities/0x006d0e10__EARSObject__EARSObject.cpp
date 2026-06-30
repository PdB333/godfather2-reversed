// FUNC_NAME: EARSObject::EARSObject
// Function at 0x006d0e10: Constructor with optional allocation. If allocateFlag bit 0 set, memory is allocated via a table-driven allocator.
// Base class initialization at FUN_00473a60 (likely sets vtable/defaults). Allocator table obtained from FUN_009c8f80.
// Offsets: allocator vtable[+0] = vtable pointer; allocator vtable[+4] = allocation function (takes this pointer and size 0x60).

EARSObject* __thiscall EARSObject::EARSObject(EARSObject* this, byte allocateFlag)
{
    // Call base class initializer (likely zeroes fields, sets vtable)
    FUN_00473a60();

    if (allocateFlag & 1)
    {
        // Obtain pointer to allocator function table
        int* pAllocTable = (int*)FUN_009c8f80();

        // Cast the function pointer at offset 4 of the table
        typedef void (__thiscall *AllocFunc)(void*, unsigned int);
        AllocFunc allocFunc = (AllocFunc)(*(pAllocTable + 1)); // *pAllocTable points to table base; +4 bytes = +1 for int*; dereference to get function ptr

        // Execute allocation – places object at 'this' with size 0x60 (likely the object size)
        allocFunc(this, 0x60);
    }
    return this;
}