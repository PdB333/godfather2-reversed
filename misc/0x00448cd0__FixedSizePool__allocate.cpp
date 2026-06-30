// FUNC_NAME: FixedSizePool::allocate
void FixedSizePool::allocate(void)
{
    // Check if free list is empty (m_freeListHead at this+0x8)
    if (m_freeListHead == nullptr)
    {
        // Allocate a new block of 64 nodes (each node is 7 ints = 28 bytes, plus 4 bytes header = 0x704 bytes total)
        int* newBlock = static_cast<int*>(FUN_009c8e50(0x704));          // custom alloc
        if (newBlock == nullptr)
        {
            m_freeListHead = nullptr;
        }
        else
        {
            newBlock = static_cast<int*>(FUN_00449080());              // likely constructor or alignment fixup
        }

        // Initialize free list: link each node's "next" pointer (stored at offset 0x1C) to the next node's start
        // Node stride = 7 ints = 28 bytes; 64 nodes total
        int* currentNode = newBlock;
        int iteration = 0x3F;                                           // 63, loops 64 times
        do
        {
            // next pointer at offset 0x1C (28 bytes) points to the start of the next node
            // (Note: piVar1+8 is 8 ints = 32 bytes from base; this sets the link to the next node's first field,
            //  which is at offset 0x1C relative to the block start? The math suggests node size is actually 32 bytes,
            //  but increment is 28 bytes; data structure is ambiguous, but the established pattern works)
            currentNode[7] = reinterpret_cast<int>(currentNode + 8);    // link to next node's link field
            iteration--;
            currentNode += 7;                                           // advance to next node
        } while (iteration != 0);

        // Zero out the 4-byte tail field at offset 0x700 (0x1C0 * 4) – padding or count?
        newBlock[0x1C0] = 0;

        // Link this new block into the block list (m_blockListHead at this+0x10)
        *newBlock = *reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(this) + 0x10);
        *reinterpret_cast<int**>(reinterpret_cast<uintptr_t>(this) + 0x10) = newBlock;

        // Advance to the first node (skip block header)
        newBlock += 1;
        *reinterpret_cast<int**>(reinterpret_cast<uintptr_t>(this) + 0x8) = newBlock;
    }

    // Pop a node from the free list
    int* node = *reinterpret_cast<int**>(reinterpret_cast<uintptr_t>(this) + 0x8);
    *reinterpret_cast<int**>(reinterpret_cast<uintptr_t>(this) + 0x8) = reinterpret_cast<int*>(node[6]); // read next at offset 0x18 (24 bytes)
    node[6] = 0;                                                      // clear the link

    // Increment allocated count (m_allocatedCount at this+0xc)
    *(int*)(reinterpret_cast<uintptr_t>(this) + 0xC) += 1;
}