// FUNC_NAME: PacketPool::allocatePacket
class PacketPool {
    // Pool header is stored at offset +0x10 from the PoolManager (this).
    // Pool header offsets:
    // +0x0c: pointer to free list head (next free block)
    // +0x24: total allocated count
    // +0x38: some flag or alignment value

    static bool bTrackingEnabled; // in_EAX proxy: enables allocation tracking
    static void* (*pfnAlloc)(int, int); // *DAT_012059dc

    void onPreAllocate(void* pool);   // FUN_00637910
    void onPostAllocate();            // FUN_00637960

public:
    // Allocate a fixed-size packet block (0x20 bytes) from the pool.
    // Returns pointer to the packet data, or 0 if allocation fails.
    void* allocatePacket(void* pool) {
        void* pBlock;
        int* pAllocCount;
        void** pFreeHead;

        pBlock = pfnAlloc(0, 0x20);
        if (pBlock == 0) {
            if (bTrackingEnabled) {
                pBlock = fallbackAlloc(); // FUN_00635a80
                return pBlock;
            }
            return 0;
        }

        if (bTrackingEnabled) {
            // Increment allocation count in pool header
            pAllocCount = (int*)(*(int*)((char*)pool + 0x10) + 0x24);
            *pAllocCount += 0x20;
        }

        // Insert block at head of free list
        pFreeHead = (void**)(*(int*)((char*)pool + 0x10) + 0xc);
        *(void**)pBlock = *pFreeHead;   // *puVar2 = old head
        *pFreeHead = pBlock;            // free list head = new block

        // Initialize packet metadata
        *(char*)((int)pBlock + 4) = 5;   // packet type? 
        *(char*)((int)pBlock + 5) = 0;   // flags
        *(char*)((int)pBlock + 6) = 0xff; // sequence/channel?
        *(char*)((int)pBlock + 7) = 0;    // more flags

        // Set other fields to 0
        *(int*)((int)pBlock + 12) = 0;   // offset 0x0c
        *(int*)((int)pBlock + 16) = 0;   // offset 0x10
        *(int*)((int)pBlock + 28) = 0;   // offset 0x1c

        onPreAllocate(pool);
        onPostAllocate();

        return pBlock;
    }
};