// FUNC_NAME: ResourceManager::releaseMemoryBlocks
void __thiscall ResourceManager::releaseMemoryBlocks(void* this, MemoryBlockHeader* block) {
    int originalBlock; // holds original pointer for later use

    originalBlock = block;
    // Load pointer at offset +0x14 and free the 32-byte block
    block = block->field_14; // +0x14: pointer to allocated memory
    deallocateMemory(0x20, &block);
    
    // Load pointer at offset +0x10 and free it
    block = ((MemoryBlockHeader*)originalBlock)->field_10; // +0x10
    deallocateMemory(0x20, &block);
    
    // Call base class/manager cleanup with original block pointer
    baseRelease(this, (MemoryBlockHeader*)originalBlock);
    
    // Finally, free pointer at offset +0x18
    block = ((MemoryBlockHeader*)originalBlock)->field_18; // +0x18
    deallocateMemory(0x20, &block);
}