// FUNC_NAME: computeTextureMemorySize
// Computes the memory size (in bytes) for a texture given width (in EAX), height, and format index.
// For compressed formats (0x1e..0x23), block size is 4x4; for others, block size is 1x1.
// Total bytes = ceil(width/blockWidth) * ceil(height/blockHeight) * (bitsPerBlock from table) / 8

uint __thiscall computeTextureMemorySize(int formatIndex, int height)
{
    int width; // passed implicitly in EAX (not a declared parameter)
    uint blockWidthHeight; // block dimension (1 or 4)
    uint blockBytes; // after shift: bits to bytes

    // Determine block size based on format index (compressed formats use 4x4 blocks)
    if (formatIndex >= 0x1e && formatIndex <= 0x23)
    {
        blockWidthHeight = 4;
    }
    else
    {
        blockWidthHeight = 1;
    }

    // Ceiling division for width and height
    // (blockWidthHeight - 1 + value) / blockWidthHeight gives ceil(value / blockWidthHeight)
    uint ceilWidth = ((blockWidthHeight - 1) + width) / blockWidthHeight;
    uint ceilHeight = ((blockWidthHeight - 1) + height) / blockWidthHeight;

    // Bits per block from table (each format entry is 12 bytes, first DWORD is bits per block)
    // Table base address: 0x00f15684
    int bitsPerBlock = *(int*)(0x00f15684 + formatIndex * 0xc);

    // Total size in bytes = number of blocks * bitsPerBlock / 8
    return (ceilWidth * ceilHeight * bitsPerBlock) >> 3;
}