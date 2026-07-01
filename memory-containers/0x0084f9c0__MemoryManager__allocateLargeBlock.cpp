// FUNC_NAME: MemoryManager::allocateLargeBlock
undefined4 MemoryManager::allocateLargeBlock(uint param_1, uint param_2, uint size)
{
    uint adjustedSize;
    undefined4 *memoryManager;
    undefined4 blockDescriptor[3]; // local_c, local_8, local_4; 12-byte struct
    void *allocatedBlock;
    
    adjustedSize = size + 0x2000;
    if (adjustedSize < 0x100000) {
        adjustedSize = 0x100000;
    }
    
    memoryManager = (undefined4 *)getGlobalMemoryManager(); // FUN_009c89b0
    blockDescriptor[0] = 0;
    blockDescriptor[1] = 0;
    blockDescriptor[2] = 0;
    
    allocatedBlock = (void *)(*(code *)*memoryManager)(adjustedSize, blockDescriptor); // virtual allocate
    if (allocatedBlock != NULL) {
        initializeLargeBlock(allocatedBlock, adjustedSize, 1, 0, (code *)0x0084f9a0, 0); // FUN_00647e90
        return 1;
    }
    return 0;
}