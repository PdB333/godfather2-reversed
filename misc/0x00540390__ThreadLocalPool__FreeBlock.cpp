// FUNC_NAME: ThreadLocalPool::FreeBlock

#include <windows.h>

// Global TLS index (from DAT_01139810)
extern DWORD g_tlsAllocatorIndex;

// Validation function at 0x00561850
extern void ValidatePointer(void* ptr);

// Debug assertion function at 0x00aa21e0
extern void FatalAssert(int code, void* ptr, int subcode);

// Per-thread pool allocator state (offsets relative to TLS block)
struct ThreadLocalAllocator {
    // ... +0x00: other fields
    int maxFreeCount;   // +0x34
    // ... unknown (+0x38 to +0x94)
    void* freeListHead; // +0x98
    int freeCount;      // +0x9c
};

void __fastcall ThreadLocalPool::FreeBlock(void* ptr)
{
    ValidatePointer(ptr);

    if (ptr != nullptr)
    {
        ThreadLocalAllocator* alloc = (ThreadLocalAllocator*)TlsGetValue(g_tlsAllocatorIndex);
        if (alloc->freeCount >= alloc->maxFreeCount)
        {
            // Free list overflow – likely double free or segmentation issue
            FatalAssert(0xc, ptr, 0xd);
            return;
        }

        alloc->freeCount++;
        *(void**)ptr = alloc->freeListHead;   // link into free list
        alloc->freeListHead = ptr;
    }
}