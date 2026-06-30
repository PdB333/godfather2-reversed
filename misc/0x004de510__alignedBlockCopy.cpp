// FUNC_NAME: alignedBlockCopy

/**
 * Optimized memory copy function that copies data in 16-byte aligned blocks,
 * with additional cache-line (64-byte) alignment handling.
 * 
 * @param dst   Destination pointer (must be writable)
 * @param src   Source pointer (must be readable)
 * @param size  Number of bytes to copy
 */
void __thiscall alignedBlockCopy(void* dst, const void* src, uint size)
{
    // Handle misalignment: copy 16-byte chunks until dst is 64-byte aligned
    uint misalign = (uint)dst & 0x3F;  // check lower 6 bits (64-byte alignment)
    while ((misalign != 0) && (size != 0))
    {
        // Copy 16 bytes (4 dwords) at a time
        *(uint32_t*)dst = *(uint32_t*)src;
        ((uint32_t*)dst)[1] = ((uint32_t*)src)[1];
        ((uint32_t*)dst)[2] = ((uint32_t*)src)[2];
        ((uint32_t*)dst)[3] = ((uint32_t*)src)[3];
        dst = (uint32_t*)dst + 4;
        src = (uint32_t*)src + 4;
        size -= 16;
        misalign = (uint)dst & 0x3F;
    }

    // Copy full 64-byte cache lines (4×16 bytes each)
    if (size > 0x40)
    {
        int64_t fullLines = (size - 0x41) >> 6;  // number of 64-byte blocks
        fullLines += 1;                           // adjust for the loop logic
        do
        {
            // Copy first 16 bytes
            *(uint32_t*)dst = *(uint32_t*)src;
            ((uint32_t*)dst)[1] = ((uint32_t*)src)[1];
            ((uint32_t*)dst)[2] = ((uint32_t*)src)[2];
            ((uint32_t*)dst)[3] = ((uint32_t*)src)[3];
            // Second 16 bytes
            ((uint32_t*)dst)[4] = ((uint32_t*)src)[4];
            ((uint32_t*)dst)[5] = ((uint32_t*)src)[5];
            ((uint32_t*)dst)[6] = ((uint32_t*)src)[6];
            ((uint32_t*)dst)[7] = ((uint32_t*)src)[7];
            // Third 16 bytes
            ((uint32_t*)dst)[8] = ((uint32_t*)src)[8];
            ((uint32_t*)dst)[9] = ((uint32_t*)src)[9];
            ((uint32_t*)dst)[10] = ((uint32_t*)src)[10];
            ((uint32_t*)dst)[11] = ((uint32_t*)src)[11];
            // Fourth 16 bytes
            ((uint32_t*)dst)[12] = ((uint32_t*)src)[12];
            ((uint32_t*)dst)[13] = ((uint32_t*)src)[13];
            ((uint32_t*)dst)[14] = ((uint32_t*)src)[14];
            ((uint32_t*)dst)[15] = ((uint32_t*)src)[15];
            src = (uint32_t*)src + 16;
            dst = (uint32_t*)dst + 16;
            size -= 0x40;
            fullLines--;
        } while (fullLines != 0);
    }

    // Copy remaining 16-byte chunks (if any)
    while (size != 0)
    {
        *(uint32_t*)dst = *(uint32_t*)src;
        ((uint32_t*)dst)[1] = ((uint32_t*)src)[1];
        ((uint32_t*)dst)[2] = ((uint32_t*)src)[2];
        ((uint32_t*)dst)[3] = ((uint32_t*)src)[3];
        src = (uint32_t*)src + 4;
        dst = (uint32_t*)dst + 4;
        size -= 16;
    }
}