// FUNC_NAME: InitializeResourcePools
void InitializeResourcePools(void)
{
    unsigned int poolHandle;
    int status;

    // Create resource pool for type 3: buffer size 0x100c0, count 1, alignment 1, flags 0xFFF
    poolHandle = allocateResourcePool(3, 0x100c0, 1, 1, 1, 0xFFF);
    status = getPoolAvailableCount(poolHandle, 4);
    if (status == -1) {
        handlePoolError(poolHandle, 0);
    }

    // Create resource pool for type 8: buffer size 0x10080, count 0x10, alignment 0x10, flags 0xFFB
    poolHandle = allocateResourcePool(8, 0x10080, 0x10, 0x10, 1, 0xFFB);
    status = getPoolAvailableCount(poolHandle, 0x100);
    if (status == -1) {
        handlePoolError(poolHandle, 0);
    }
}