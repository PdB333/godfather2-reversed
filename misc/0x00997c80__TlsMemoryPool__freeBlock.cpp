// FUNC_NAME: TlsMemoryPool::freeBlock
void __fastcall TlsMemoryPool::freeBlock(TlsAllocationInfo *allocInfo)
{
    // allocInfo layout:
    // +0x00: poolId (uint)
    // +0x04: unknown (uint)
    // +0x08: blockIndex (int) - index into block pool, -1 if invalid
    int blockIndex = allocInfo->blockIndex;
    if (blockIndex >= 0) {
        // Retrieve thread-local storage pointer (unused here, side effect? may set up context)
        TlsGetValue(gTlsSlot); // DAT_01139810 - global TLS slot index for memory pools
        // Free block: poolId, block size = blockIndex << 4, type = 0x17 (likely memory zone tag)
        FUN_00aa26e0(allocInfo->poolId, blockIndex << 4, 0x17);
    }
}