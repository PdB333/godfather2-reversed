// FUNC_NAME: MemoryManager::allocateAndConstructObject
undefined4 MemoryManager::allocateAndConstructObject(void)
{
    // Get the singleton memory manager instance
    MemoryManager* memMgr = (MemoryManager*)MemoryManager::getInstance(); // FUN_009c8f80

    // Allocation parameters: poolType=2, alignment=0x10, flags=0
    struct AllocationParams {
        int poolType;   // +0x00: probably memory pool identifier
        int alignment;  // +0x04: requested alignment
        int flags;      // +0x08: allocation flags
    } params = {2, 0x10, 0}; // local_c, local_8, local_4

    // Call the allocator's virtual function at vtable+0 (allocate)
    int success = memMgr->allocate(0xb0, &params); // size 176 bytes

    if (success != 0) {
        // Call the constructor/initializer on the allocated memory
        return constructObject(); // FUN_0082da00
    }
    return 0;
}