// FUNC_NAME: SlotAllocator::releaseHandle
// Address: 0x005564f0
// Role: Releases a slot handle from a thread-local memory pool. If the slot index (at +0x08) is valid,
// retrieves the TLS pointer to the pool and calls poolFree with the base address, slot index * 64, and a constant 0x17 (size/type flag).

void __fastcall SlotAllocator::releaseHandle(void)
{
    int slotIndex = *(int*)((char*)this + 8);          // +0x08: slot index
    if (slotIndex >= 0)
    {
        void* poolBase = TlsGetValue(gTlsPoolIndex);  // global TLS index for pool
        // Free block: base = *(void**)this (at +0x00), offset = slotIndex << 6 (64 bytes per slot), size 0x17
        MemoryPool::freeBlock(*(void**)this, slotIndex << 6, 0x17);
    }
    return;
}