// FUNC_NAME: PoolAllocatedObject::PoolAllocatedObject
// Address: 0x00552300
// Constructor that optionally allocates memory from a thread-local storage (TLS) allocator.
// If param_2 & 1 is set, it allocates a buffer of size (*(uint16_t*)(this+4)) using a TLS pool,
// with a fixed allocation constant 0x34 (52 bytes) – likely an alignment or metadata size.

int __thiscall PoolAllocatedObject::PoolAllocatedObject(void* thisPtr, byte flags)
{
    // Call base class constructor (e.g., EARSObject or MemoryObject)
    BaseClass::Constructor(); // FUN_005525d0 assumed to be a base constructor

    // If the lowest bit of flags is set, perform a TLS-based memory allocation
    if ((flags & 1) != 0)
    {
        // Retrieve thread-local storage pointer (e.g., allocator instance)
        void* tlsAllocator = TlsGetValue(DAT_01139810); // TLS handle for allocator

        // Allocate additional memory for the object using the size at offset +0x04 (uint16)
        // and a fixed constant 0x34 (possibly alignment or chunk size)
        FUN_00aa26e0(thisPtr, *(uint16_t*)((char*)thisPtr + 0x04), 0x34);
    }

    return (int)thisPtr;
}