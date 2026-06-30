// FUNC_NAME: MemoryPool::releaseAll
// Address: 0x00573910
// This function releases all allocated blocks back to the free list and clears the used list.
// The memory pool maintains:
//   +0x00: slotArray[] - array of linked list heads per slot (each slot holds a list of blocks)
//   +0x04: slotCount   - number of slots in the array
//   +0x08: freeListHead - head of the free list (blocks available for allocation)
//   +0x0C: freeCount    - number of blocks currently in the free list? (decremented as blocks are added)
//   +0x10: usedListHead - head of a separate list of blocks that need special cleanup (external allocations?)
// Each block has at +0x0C a 'next' pointer linking blocks in a singly linked list.

void MemoryPool::releaseAll()
{
    int* currentBlock;
    int** slotArray;       // this+0x00
    int slotCount;         // this+0x04
    int* freeListHead;     // this+0x08
    int freeCount;         // this+0x0C
    int* usedListHead;     // this+0x10

    // Free all blocks in each slot's list by moving them to the free list
    for (unsigned int slot = 0; slot < slotCount; slot++)
    {
        int* block = slotArray[slot];
        if (block != nullptr)
        {
            // Traverse the singly linked list of blocks in this slot
            do
            {
                currentBlock = (int*)(block[3]); // offset +0x0C is 'next' pointer
                // Add block to free list (head insertion)
                block[3] = (int)freeListHead;
                freeCount--;
                freeListHead = block;
                block = currentBlock;
            } while (currentBlock != nullptr);
            // Clear the slot's head pointer
            slotArray[slot] = nullptr;
        }
    }

    // Free all blocks in the separate used list (external allocations that need destructor call)
    int* nextUsed;
    int* used = usedListHead;
    while (used != nullptr)
    {
        nextUsed = (int*)*used; // first field of the used block is the next pointer? Or is it a pointer to the object? Assuming it's a linked list with 'next' at offset 0.
        // Call destructor or cleanup function for each block in the used list
        FUN_009c8eb0(used);
        used = nextUsed;
    }

    // Reset list heads and free count
    usedListHead = nullptr;
    freeListHead = nullptr;
    freeCount = 0; // Usually reset to initial value, but here it's set to 0. Possibly the freeCount tracks available blocks, now all are free but count is reset.
}