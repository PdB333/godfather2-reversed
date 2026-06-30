// FUNC_NAME: FreeListAllocator::init
void __fastcall FreeListAllocator::init(void* unk, void* pool, void** outPool)
{
    // +0x00: head pointer (free list start)
    // +0x0C: pointer to the start of the buffer pool (pool + 0x0D words)
    // +0x10: pointer to the end of the buffer pool (pool + 0x8D words)
    // +0x8D words: sentinel value (0x7DCC) marking end of free list
    // +0x00 of buffer: first free slot

    int* poolInt = (int*)pool;
    int* bufferStart = poolInt + 0xD;
    poolInt[3] = (int)bufferStart;          // +0x0C = start of buffer

    // Zero-initialize 128 entries (0x80 * 4 bytes)
    int* cur = bufferStart;
    for (int i = 0x80; i != 0; i--)
    {
        *cur = 0;
        cur++;
    }

    int* bufferEnd = poolInt + 0x8D;
    poolInt[4] = (int)bufferEnd;            // +0x10 = end of buffer

    // Store sentinel at end of buffer
    *bufferEnd = 0x7DCC;

    // Initialize head pointer with the sentinel value (empty list)
    *poolInt = *bufferEnd;

    // Clear fields at end-of-buffer + 8 and +4 (unused?)
    *(bufferEnd + 2) = 0;                   // e.g., count or tail?
    *(int*)((char*)bufferEnd + 4) = 0;

    // Clear additional struct fields
    poolInt[5] = 0;                         // +0x14
    poolInt[6] = 0;                         // +0x18

    *outPool = pool;
}