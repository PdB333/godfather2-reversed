// FUNC_NAME: FixedAllocator::initialize
// Address: 0x005f5830
// Initializes a fixed-size block allocator (free list) by allocating memory and linking all blocks.
// Returns 1 on success, 0 on failure (null pointer or allocation failure).

class FixedAllocator {
public:
    // Fields (offsets relative to this):
    // +0x00: m_pFreeList (head of free list, initially points to first block)
    // +0x04: m_pBuffer   (start of allocated memory, same as m_pFreeList initially)
    // +0x08: m_nCapacity (number of blocks)
    // +0x0C: m_nCount    (number of free blocks, initially equals capacity)
    // +0x10: m_nBlockSize (size of each block in bytes)
    // ... (may contain additional fields)

    enum AllocFlags : int {
        kAlign2 = 2,
        kAlign4 = 4,
        kNoFlag = 0
    };

    // Global allocator pointer (from DAT_01223518)
    // This points to a struct whose first member is a function table with an allocation function (__thiscall).
    // Allocation signature: void* (*)(size_t size, AllocFlags* flags)
    extern void* g_pHeapAllocator; // actually (void**)DAT_01223518

    // External function: enters critical section (or acquires lock)
    // Probably: void PoolLock::enter()
    void __thiscall enterPoolLock();

    // External function: memset (standard library)
};

int __thiscall FixedAllocator::initialize(int nCount, int nBlockSize, void (*pConstructor)(void*))
{
    int nTotalSize;    // product of count and block size
    void* pNewBuffer;  // allocated memory
    int i;             // loop counter
    void* pCurrent;    // current block in free list linking
    void* pNext;       // next block address

    // Self-check: pointer 'this' must be non-null
    if (this == nullptr) {
        return 0;
    }

    nTotalSize = nCount * nBlockSize;

    // Acquire pool lock
    enterPoolLock();

    // Check if global heap allocator exists and size is non-zero
    if (g_pHeapAllocator != nullptr && nTotalSize != 0) {
        // Prepare allocation flags: alignment 2 and 4, no flags
        AllocFlags allocFlags[3] = { kAlign2, kAlign4, kNoFlag };

        // Call the global allocator's allocation function (first vtable entry)
        // vtable pointer is at *(void**)g_pHeapAllocator
        // The allocator function takes (size_t size, AllocFlags* flags)
        typedef void* (__thiscall *AllocFunc)(void* pThis, size_t size, AllocFlags* flags);
        AllocFunc pfnAlloc = *(AllocFunc*) *(void**)g_pHeapAllocator;
        pNewBuffer = pfnAlloc(g_pHeapAllocator, nTotalSize, allocFlags);

        if (pNewBuffer != nullptr) {
            // Set flag: bit 0 in m_nFlags (at offset +0x14? but we don't have that field)
            // Actually the code sets: in_EAX[5] = in_EAX[5] | 1; so there is a flags field at +0x14
            // We'll call it m_nFlags and set the "initialized" bit.
            this->flags |= 1;

            // Zero out the entire buffer
            memset(pNewBuffer, 0, nTotalSize);

            // Initialize allocator fields
            this->pFreeList = pNewBuffer;       // +0x00
            this->pBuffer   = pNewBuffer;       // +0x04
            this->capacity  = nCount;           // +0x08
            this->freeCount = nCount;           // +0x0C
            this->blockSize = nBlockSize;       // +0x10

            // Link all blocks into a free list (each block points to the next)
            // The stride between blocks is nBlockSize (passed as unaff_retaddr)
            pCurrent = pNewBuffer;
            for (i = 0; i < nCount; i++) {
                // Compute address of next block
                pNext = (void*)((char*)pCurrent + nBlockSize);
                // Write the next pointer at the beginning of current block
                *(void**)pCurrent = pNext;

                // If a constructor function was provided (via some hidden parameter), call it.
                // In the decompile, a function pointer was conditionally called here.
                // It appears it might be passed in a register (e.g., unaff_retaddr is actually the callback).
                // We'll assume it's a separate parameter pConstructor.
                if (pConstructor != nullptr) {
                    pConstructor(pCurrent);
                }

                // Advance to next block
                pCurrent = pNext;
            }

            // The last block's next pointer now points beyond the buffer.
            // In the original code, it is set to point back to the FixedAllocator object.
            // This creates a sentinel: when the free list head equals the object, it's empty.
            // Adjust the last block's pointer.
            // Since we already set pNext for the last iteration, we need to fix the pointer that was written.
            // The loop wrote pNext for the last block, but we need to change it to point to 'this'.
            // The decompile does: *(undefined4 **)((int)_Dst - unaff_retaddr) = in_EAX;
            // Which sets the "next" pointer of the block before the sentinel? Actually it's confusing.
            // Let's match the effect: The last block's next should be 'this' object.
            // The loop already set it, so we overwrite correctly.
            // We'll do: at the end, compute address of the block before the sentinel.
            // The index of the last block is nCount-1.
            // But we can simply recalc: the block that is exactly at (buffer + nBlockSize * (nCount-1))
            // Its next pointer should be this object.
            // However the loop wrote pNext as buffer + nBlockSize*nCount (past the buffer) for the last block.
            // So we overwrite that:
            void* lastBlock = (void*)((char*)pNewBuffer + nBlockSize * (nCount - 1));
            *(void**)lastBlock = (void*)this;

            return 1;
        }
    }
    return 0;
}