// FUNC_NAME: BitAllocator::tryAllocateBit
// Reconstructed from 0x00665720 - tries to allocate a bit index in a bitmap, returns 0 on success, non-zero on failure
// Structure offsets:
// +0x00: int m_allocatedChunkCount; // number of chunks with at least one bit set? Set to (bitIndex/28)+1 on success
// +0x04: int m_bitmapSizeWords; // number of 32-bit words in the bitmap
// +0x08: int m_reserved; // always set to 0
// +0x0C: unsigned int* m_bitmap; // pointer to the raw bitmap memory
// The bitmap is divided into chunks of 28 bits each (each word holds one chunk, bits 0-27 used).
// FUN_00667740 is an external check (likely returns non-zero if the bit would cause overflow/duplicate)

int BitAllocator::tryAllocateBit(int bitIndex)
{
    // Reset structure (assumes first call or reinit? Actually always resets – maybe this is a reinit+set)
    this->m_reserved = 0;
    this->m_allocatedChunkCount = 0;
    _memset(this->m_bitmap, 0, this->m_bitmapSizeWords * sizeof(unsigned int));

    int chunkIndex = bitIndex / 0x1c; // 28 bits per chunk
    int bitOffset = bitIndex % 0x1c; // shift within the word (0-27)

    int result = FUN_00667740(); // external check (e.g., maximum chunks, uniqueness test)
    if (result == 0)
    {
        // Mark bit as used
        this->m_allocatedChunkCount = chunkIndex + 1;
        this->m_bitmap[chunkIndex] = 1 << bitOffset;
        result = 0;
    }
    return result;
}