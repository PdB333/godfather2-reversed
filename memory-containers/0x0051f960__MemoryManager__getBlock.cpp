// FUNC_NAME: MemoryManager::getBlock
int* __fastcall MemoryManager::getBlock(int this)
{
    int* pFreeBlock = *(int**)(this + 0x474); // free list head
    if (pFreeBlock != nullptr)
    {
        *(int**)(this + 0x474) = (int*)pFreeBlock[0x10]; // pop next free block
        return pFreeBlock;
    }

    int* pCurrent = *(int**)(this + 4);   // linked list head (e.g., pool list)
    int* pBest = nullptr;
    float bestFloat = DAT_00e2eff4;       // sentinel value (e.g., -infinity)

    // Traverse the pool list to find the pool with the largest available chunk
    while (pCurrent != *(int**)(this + 0xc)) // tail sentinel
    {
        float candidateFloat = DAT_00e2eff4;
        // Check if pool's internal free list is non-empty (offset 0x14 != offset 0x1c)
        if (*(int*)(pCurrent + 0x14) != *(int*)(pCurrent + 0x1c))
        {
            // Get the float from the first free block's header (offset 0x14 of pool structure)
            candidateFloat = *(float*)(*(int*)(pCurrent + 0x14) + 0x14);
        }

        if (bestFloat < candidateFloat)
        {
            pBest = pCurrent;
            bestFloat = candidateFloat;
        }

        pCurrent = *(int**)(pCurrent + 0x2c); // next pool in list
    }

    // If we found a pool with available blocks, remove one from its internal free list
    if (pBest != nullptr)
    {
        int* pBlock = *(int**)(pBest + 0x14); // first free block in pool
        if (pBlock != nullptr && pBlock != *(int**)(pBest + 0x1c)) // not empty?
        {
            // Unlink the block from the doubly linked free list
            // Block layout: +0x40 = next, +0x44 = prev
            *(int*)(pBlock[0x11] + 0x40) = pBlock[0x10]; // prev->next = next
            *(int*)(pBlock[0x10] + 0x44) = pBlock[0x11]; // next->prev = prev

            // Call virtual function on the block (probably initialize or return)
            (**(code**)(*pBlock + 4))(); // vtable+4

            return pBlock;
        }
    }

    return nullptr;
}