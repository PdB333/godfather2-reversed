// FUNC_NAME: HeapManager::allocate
int* __thiscall HeapManager::allocate(int size)
{
    // Align size to 4 bytes and add 4 bytes header overhead
    int alignedSize = ((size - 1) + ((size - 1) >> 31 & 3)) >> 2 * 4; // rounds down to multiple of 4
    int blockSize = alignedSize + 4; // total block size including header

    // Check the sorted free list for a suitable block
    FreeBlock* freeBlock = reinterpret_cast<FreeBlock*>(this->freeList); // +0x10
    while (freeBlock != nullptr)
    {
        if (blockSize <= freeBlock->size) // first field is size
            goto foundBlock;
        freeBlock = freeBlock->next; // +4 (offset 1)
    }

    // No suitable block found – try coalescing pending deallocations
    while (true)
    {
        Block* pending = reinterpret_cast<Block*>(this->pendingFreeList); // +0x18
        if (pending == nullptr)
            return nullptr; // out of memory

        // Remove 'pending' from its containing list (either bucket or doubly linked list)
        if (pending->bucketPrev == nullptr)
        {
            // Update the bucket array pointer (hash table based on size)
            int bucketIndex = (static_cast<unsigned short>(pending->field60) * 16 +
                               static_cast<unsigned short>(pending->field62) +
                               *(reinterpret_cast<int*>(pending) + 25)) & 0x7f; // +100 (offset 25 words)
            *reinterpret_cast<int*>(this->bucketArray + bucketIndex * 4) = pending->next;
        }
        else
        {
            *reinterpret_cast<int*>(pending->bucketPrev + 4) = pending->next; // offset +4 (next field)
        }

        if (pending->prev != nullptr)
        {
            *reinterpret_cast<int*>(pending->prev + 8) = pending->next; // offset +8
        }

        // Remove from pending list
        int next = pending->pendingNext; // +0xc
        this->pendingFreeList = next; // +0x18
        if (next == 0)
            this->pendingFreeListTail = 0; // +0x14
        else
            *reinterpret_cast<int*>(next + 0x10) = 0;

        // Insert this block back into the free list (function at 0x00672dc0)
        freeBlock = reinterpret_cast<FreeBlock*>(FUN_00672dc0());
        if (blockSize <= freeBlock->size)
            goto foundBlock;
    }

foundBlock:
    // Split the free block: take blockSize bytes from the end
    int* allocatedBlock = reinterpret_cast<int*>(reinterpret_cast<char*>(freeBlock) + (freeBlock->size - blockSize));
    *allocatedBlock = blockSize; // store block size in header
    freeBlock->size -= blockSize; // shrink remaining free block

    this->lastAllocatedBlock = allocatedBlock; // +0x08
    return allocatedBlock;
}