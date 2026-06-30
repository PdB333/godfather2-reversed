// FUNC_NAME: PoolAllocator::allocateNode
// Address: 0x006f5810
// Allocates a fixed-size node (16 bytes) from a pool. Lazily allocates 256-node blocks.
// Returns pointer to the allocated node.

void* __fastcall PoolAllocator::allocateNode(int thisPtr)
{
    int* freeListHead = *(int**)(thisPtr + 8);   // +0x08: free list head pointer
    if (freeListHead == nullptr)
    {
        // Allocate a new block: 256 nodes * 16 bytes = 0x1000, plus 4 bytes sentinel = 0x1004
        freeListHead = (int*)allocateMemory(0x1004);
        int* nodeIter = freeListHead;
        for (int i = 0; i < 256; i++)
        {
            // Build the free list: each node's "next" pointer is stored at offset 0x0C? Actually we set at offset 0x10
            // This initialization is unusual but we keep the original logic.
            nodeIter[4] = (int)(nodeIter + 5);   // node[4] = &node[5] (offset 0x10 points to 0x14)
            nodeIter += 4;                       // advance by 16 bytes to next node
        }
        freeListHead[0x400] = 0;                // last 4 bytes of the block set to 0 (sentinel)
        // Add this block to the block list (first 4 bytes of block become previous block head)
        *freeListHead = *(int*)(thisPtr + 0x10); // +0x10: block list head
        *(int**)(thisPtr + 0x10) = freeListHead; // update block list head
        // Free list head becomes the second int of the block (start of first node)
        freeListHead = freeListHead + 1;
        *(int**)(thisPtr + 8) = freeListHead;
    }
    // Pop the head node from the free list
    int* allocatedNode = freeListHead;
    int* nextFree = (int*)allocatedNode[3];     // next pointer at offset 0x0C
    *(int**)(thisPtr + 8) = nextFree;           // update free list head
    allocatedNode[3] = 0;                       // clear next pointer of allocated node
    (*(int*)(thisPtr + 0xC))++;                 // +0x0C: increment allocation count
    return allocatedNode;
}