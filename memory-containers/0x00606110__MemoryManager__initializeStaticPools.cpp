// FUNC_NAME: MemoryManager::initializeStaticPools

void MemoryManager::initializeStaticPools(void)
{
    int poolHandleA;
    int allocationIndex;

    // Create first pool: type=3, size=0x100c0, alignment=1, unknown=1, flags=0xfff
    poolHandleA = poolCreate(3, 0x100c0, 1, 1, 1, 0xfff);
    allocationIndex = poolAllocate(poolHandleA, 4);
    if (allocationIndex == -1) {
        poolReset(poolHandleA, 0);
    }

    // Create second pool: type=8, size=0x10080, numBlocks=16, alignment=0x10, unknown=1, flags=0xffb
    poolHandleA = poolCreate(8, 0x10080, 0x10, 0x10, 1, 0xffb);
    allocationIndex = poolAllocate(poolHandleA, 0x100);
    if (allocationIndex == -1) {
        poolReset(poolHandleA, 0);
    }
}