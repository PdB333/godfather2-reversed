// FUNC_NAME: MemoryManager::changeBlockAllocation
void __thiscall MemoryManager::changeBlockAllocation(void* thisPtr)
{
    // thisPtr is the instance of MemoryManager
    // Offset 0x5C: Pointer to an array of block headers (likely a pool or free list)
    int* blockHeaderArray = *(int**)((int)thisPtr + 0x5C);

    // FUN_00777310 returns a new block identifier or pointer (maybe from allocation request)
    int newBlockValue = FUN_00777310();
    if (newBlockValue != 0)
    {
        // Slot at index 0x1D3 (467) in the block header array holds the current block info
        int currentBlock = blockHeaderArray[0x1D3]; // current block value
        int* currentBlockPtr = &blockHeaderArray[0x1D3];

        // Check if current block already matches the requested new block
        // 0x48 (72) seems to be a header size or a sentinel value
        if (currentBlock == 0 || currentBlock == 0x48 || (currentBlock - 0x48) != newBlockValue)
        {
            // If not matching, call a virtual function at vtable offset 0x260
            // This likely removes or detaches the current block from a linked list
            (*(void(__thiscall**)(int*))(*(int*)blockHeaderArray + 0x260))();

            // Calculate new block offset (header + new data)
            int newBlockOffset = newBlockValue + 0x48;

            if (currentBlock != newBlockOffset)
            {
                // If there is an old block, remove it from its linked list
                if (currentBlock != 0)
                {
                    FUN_004daf90(currentBlockPtr);
                }

                // Assign new block offset to the slot
                *currentBlockPtr = newBlockOffset;

                if (newBlockOffset != 0)
                {
                    // Insert the new block into a doubly-linked list
                    // Offset 0x4C in the new block's header contains the next pointer
                    blockHeaderArray[0x1D4] = *(int*)(newBlockValue + 0x4C);
                    *(int**)(newBlockValue + 0x4C) = currentBlockPtr;
                }
            }
        }
    }
    return;
}