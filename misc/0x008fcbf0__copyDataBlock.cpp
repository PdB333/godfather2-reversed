// FUNC_NAME: copyDataBlock
// Address: 0x008fcbf0
// Copies data from source to destination with a specific stride pattern.
// The source structure has a count at offset 0x40 and data at offset 0xc.
// Each iteration copies 16 bytes (4 uint32), with source and destination pointers advancing by 4 bytes,
// producing a sliding window effect. This may be used for copying transforms or matrices.

void copyDataBlock(void *dest, void *src)
{
    uint count = *(uint *)((char *)src + 0x40); // +0x40: number of elements to copy
    if (count != 0)
    {
        uint32_t *srcPtr = (uint32_t *)((char *)src + 0xc); // +0xc: start of source data area
        uint32_t *destPtr = (uint32_t *)((char *)dest + 4); // +0x4: start of destination data area
        for (uint i = 0; i < count; i++)
        {
            // Copy 4 consecutive uint32 values from srcPtr-3..srcPtr to destPtr-1..destPtr+2
            destPtr[-1] = srcPtr[-3];
            destPtr[0]  = srcPtr[-2];
            destPtr[1]  = srcPtr[-1];
            destPtr[2]  = srcPtr[0];
            srcPtr += 4;
            destPtr += 4;
        }
    }
    return;
}