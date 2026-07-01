// FUNC_NAME: MemoryPoolObject::~MemoryPoolObject
void __fastcall MemoryPoolObject::~MemoryPoolObject(void* thisPtr)
{
    uint allocIdx = *(uint*)((char*)thisPtr + 0x18); // +0x18: index into thread-local memory pool
    *(void**)thisPtr = (void*)&PTR_DTOR_VTABLE1;     // Set vtable to first destructor entry

    if ((int)allocIdx >= 0) {
        void* tlsHeap = TlsGetValue(DAT_01139810);  // Retrieve thread-local heap handle
        void* dataPtr = *(void**)((char*)thisPtr + 0x10); // +0x10: pointer to allocated data block
        uint size = (allocIdx & 0x3FFFFFFF) * 0x30; // Calculate size from index, pool block size = 0x30
        FUN_00aa26e0(dataPtr, size, 0x17);          // Deallocate memory (likely custom heap free)
    }

    *(void**)thisPtr = (void*)&PTR_DTOR_VTABLE2;     // Switch to base destructor vtable
}