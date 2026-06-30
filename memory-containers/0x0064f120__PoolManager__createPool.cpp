// FUNC_NAME: PoolManager::createPool

undefined4* PoolManager::createPool(void)
{
    undefined4 *poolEntry;
    undefined4 resourceHandle;

    // Set the global resource ID for this pool (0x3ff8)
    g_resourceId = 0x3ff8;

    // Allocate memory for pool entry structure (0xC bytes)
    poolEntry = (undefined4 *)allocMemory(0xC);
    if (poolEntry == (undefined4 *)0x0) {
        poolEntry = (undefined4 *)0x0;
    }
    else {
        // Allocate the actual resource data associated with this ID
        resourceHandle = allocResource(0x3ff8);
        poolEntry[1] = resourceHandle; // +0x04: resource handle
    }

    // Store pool entry pointer globally
    g_poolEntry = poolEntry;

    // Initialize pool entry fields
    *poolEntry = 0;                  // +0x00: count or flags
    g_poolEntry[2] = 0;             // +0x08: next pointer or additional field

    // Initialize other global pool state
    g_poolState0 = 0;
    g_poolElementSize = 0xC;        // Size of each element
    g_poolState1 = 0;

    // Return address of the global pool entry pointer
    return &g_poolEntry;
}