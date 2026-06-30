// FUNC_NAME: MemoryAllocator::initializePool
int MemoryAllocator::initializePool(MemoryPoolHandle *outHandle)
{
    // Allocate internal pool data: 4 blocks of 0x40 bytes each (total 0x100 bytes)
    MemoryPoolData *poolData = static_cast<MemoryPoolData*>(calloc(4, 0x40));
    if (poolData == nullptr) {
        return -2; // Allocation failure
    }

    // Read the current block count from the global allocator context (likely this or a singleton)
    int blockIndex = *m_blockCount;  // in_EAX -> m_blockCount
    uint poolSize; // local_10
    uint blockSize = 0x40; // local_c
    uint flags = 0; // local_8

    if (blockIndex == 0) {
        poolSize = 0;
    } else {
        // Compute the base size: (blockIndex-1) * 0x1c
        poolSize = (blockIndex - 1) * 0x1c;
        // Read the bitmask from the pool configuration array (located at m_config + blockIndex*4)
        uint bitmask = *(uint*)(m_config + (blockIndex * 4) - 4);
        // Count how many bits are needed to represent the bitmask (i.e., highest set bit index)
        while (bitmask != 0) {
            bitmask >>= 1;
            poolSize++;
        }
    }

    int error = FUN_00665720(poolSize); // Possibly align or reserve memory for the pool
    if (error == 0) {
        // Define the memory region to be managed: offset=0, size=0x40, flags=0
        MemoryRegion region;
        region.baseOffset = 0;
        region.size = 0x40;
        region.flags = 0;

        error = FUN_0066c8d0(&region); // Insert this region into the free-list / manage it
        if (error == 0) {
            // Success: store the allocated pool data into the output handle
            *outHandle = poolData;
            FUN_00665b40(); // Finalize/sync the allocator (e.g., release lock or update metadata)
            return 0;
        }
    }

    // Error path: clean up if any step failed
    FUN_00665b40();
    return error;
}