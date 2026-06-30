// FUNC_NAME: MemoryBlockPool::popBlockWithCallback
void __thiscall MemoryBlockPool::popBlockWithCallback(void* this, void (*callback)(uint32_t, uint32_t, uint32_t))
{
    // +0x18: pointer to current block in a linear linked list of 12-byte entries
    uint32_t* currentBlockPtr = *(uint32_t**)((uint32_t)this + 0x18);
    // Align to next 4-byte boundary (round up to multiple of 4)
    uint32_t* alignedBlockPtr = (uint32_t*)(((uint32_t)currentBlockPtr + 3) & 0xFFFFFFFC);
    
    // Read the second 32-bit word (offset +4) as block size/identifier
    uint32_t blockParam = alignedBlockPtr[1];
    
    // Store the aligned pointer back, marking this block as the current one
    *(uint32_t**)((uint32_t)this + 0x18) = alignedBlockPtr;
    
    // Read the first 8 bytes of the block as two 32-bit halves
    uint64_t blockData = *(uint64_t*)alignedBlockPtr;
    uint32_t dataLow = (uint32_t)blockData;
    uint32_t dataHigh = (uint32_t)(blockData >> 32);
    
    // Advance the free list pointer to the next block (12 bytes total per block)
    *(uint32_t**)((uint32_t)this + 0x18) = alignedBlockPtr + 3; // +12 bytes
    
    // Invoke the callback with the extracted data (low, high, param)
    callback(dataLow, dataHigh, blockParam);
}