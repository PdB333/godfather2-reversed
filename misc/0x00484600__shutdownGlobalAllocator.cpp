// FUNC_NAME: shutdownGlobalAllocator

void shutdownGlobalAllocator(void)
{
    // Temporary buffer for allocator shutdown context (12 bytes)
    uint8_t shutdownContext[12];

    // Call allocator shutdown function with context and global data
    FUN_004841a0(shutdownContext, &DAT_0122399c, *DAT_012239a0, &DAT_0122399c, DAT_012239a0);

    // Release the global allocator instance
    FUN_009c8eb0(DAT_012239a0);

    // Clear globals to prevent dangling references
    DAT_012239a0 = nullptr;
    _DAT_012239a4 = 0;
}