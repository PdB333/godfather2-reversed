// FUNC_NAME: MemoryAllocator::free
// Function address: 0x00610af0
// Role: Deallocate a memory block from a fixed-size pool or via system delete.
//       Uses a global heap manager singleton at DAT_012058e0.
void __fastcall MemoryAllocator::free(void* thisPointer, void* pBlock)
{
    // Access the global heap manager singleton
    HeapManager* pHeap = reinterpret_cast<HeapManager*>(DAT_012058e0);
    if (pBlock == nullptr)
        return;

    // Pool start address (offset 0x4004 from heap manager base)
    void* pPoolStart = *(void**)(reinterpret_cast<uintptr_t>(pHeap) + 0x4004);
    if (pPoolStart == nullptr)
        return;

    // Fallback deallocator vtable pointer (offset 0x4020)
    void* pFallbackVtable = *(void**)(reinterpret_cast<uintptr_t>(pHeap) + 0x4020);
    if (pFallbackVtable != nullptr)
    {
        // Pool size (offset 0x4008)
        uint32_t poolSize = *(uint32_t*)(reinterpret_cast<uintptr_t>(pHeap) + 0x4008);
        // Check if block lies outside the pool range
        bool isOutsidePool = (pBlock < pPoolStart) ||
                             (pBlock >= reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(pPoolStart) + poolSize));
        if (isOutsidePool)
        {
            // Call the registered system deallocator (vtable entry at offset 8)
            typedef void (*DeallocFunc)(void*);
            DeallocFunc pDealloc = *(DeallocFunc*)(*(uintptr_t*)pFallbackVtable + 8);
            pDealloc(pBlock);
            return;
        }
    }

    // Pool allocation: return block to free list (singly linked list)
    // The first 4 bytes of the block store the next free pointer
    *reinterpret_cast<void**>(pBlock) = *(void**)(reinterpret_cast<uintptr_t>(pHeap) + 0x400C); // m_freeListHead

    // Increment free count (offset 0x4018)
    int* pFreeCount = reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(pHeap) + 0x4018);
    (*pFreeCount)++;

    // Update free list head to this block (offset 0x400C)
    *(void**)(reinterpret_cast<uintptr_t>(pHeap) + 0x400C) = pBlock;
}