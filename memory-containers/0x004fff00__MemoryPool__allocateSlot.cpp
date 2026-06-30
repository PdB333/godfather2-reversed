// FUNC_NAME: MemoryPool::allocateSlot
int __fastcall MemoryPool::allocateSlot(MemoryPool* thisPtr)
{
    // +0x24: likely a spinlock or mutex pointer
    sub_43e500(thisPtr + 0x24);

    int slotIndex = *(int*)((char*)thisPtr + 0x10); // +0x10: slot index to allocate

    // Access thread-local storage: FS:[0x2C] points to TLS array
    // Dereference to get base pointer of per-thread allocator data
    int* tlsBase = *(int**)(*(int*)(豋(uintptr_t)__readfsdword(0x2C)) + 0x8);
    int* slotPtr = (int*)((char*)tlsBase + slotIndex);

    // Mark slot as used by setting bit 0
    *slotPtr |= 1;

    return (int)slotPtr;
}