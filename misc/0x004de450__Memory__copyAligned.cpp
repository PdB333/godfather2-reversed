// FUNC_NAME: Memory::copyAligned
void __thiscall Memory::copyAligned(void* dest, uint size) 
// ECX (this) -> source pointer (src)
// [ESP+4] -> dest
// [ESP+8] -> size
{
    uint32_t* src = (uint32_t*)this;        // source from ECX
    uint32_t* dst = (uint32_t*)dest;        // destination from stack
    uint32_t remaining = size;

    // Align destination to a 64-byte cache line boundary
    uint alignOffset = (uint)dst & 0x3F;
    while (alignOffset != 0 && remaining != 0)
    {
        // Copy one 16-byte (4 dword) chunk
        dst[0] = src[0];
        dst[1] = src[1];
        dst[2] = src[2];
        dst[3] = src[3];
        src += 4;
        dst += 4;
        remaining -= 16;
        alignOffset = (uint)dst & 0x3F;
    }

    // Copy full 64-byte blocks (aligned) for the bulk of the data
    if (remaining > 64)
    {
        // Calculate number of 64-byte blocks
        int blockCount = (remaining - 65) / 64 + 1;
        do
        {
            // Copy 64 bytes (16 dwords) in four 16-byte writes
            dst[0] = src[0];
            dst[1] = src[1];
            dst[2] = src[2];
            dst[3] = src[3];
            dst[4] = src[4];
            dst[5] = src[5];
            dst[6] = src[6];
            dst[7] = src[7];
            dst[8] = src[8];
            dst[9] = src[9];
            dst[10] = src[10];
            dst[11] = src[11];
            dst[12] = src[12];
            dst[13] = src[13];
            dst[14] = src[14];
            dst[15] = src[15];
            src += 16;
            dst += 16;
            remaining -= 64;
            blockCount--;
        } while (blockCount != 0);
    }

    // Copy remaining bytes in 16-byte chunks
    while (remaining != 0)
    {
        dst[0] = src[0];
        dst[1] = src[1];
        dst[2] = src[2];
        dst[3] = src[3];
        src += 4;
        dst += 4;
        remaining -= 16;
    }
}