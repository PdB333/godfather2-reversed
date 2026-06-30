// FUNC_NAME: GetSizeClass (global helper for memory allocation size classes)

#include <cstdint>

// Size class lookup table (1024 entries, each byte is an offset)
// Located at: 0x00e4218f (PTR_DAT_00e4218f)
extern const uint8_t sizeClassTable[256]; // Actually 256 entries used per byte

// Returns a size class index for a given size.
// Uses a byte-level look-up to avoid branches.
// Returns 0xFFFFFFFF (-1) for size 0.
// __fastcall: size in eax, result in eax.
uint32_t __fastcall GetSizeClass(uint32_t size)
{
    if (size > 0xFFFF)
    {
        // Size > 65535: use top byte to index, add 0x18 (24 base)
        uint8_t index = (size >> 24) & 0xFF;
        return sizeClassTable[index] + 0x18;
    }
    else if (size > 0xFF)
    {
        // Size 256..65535: use second byte, add 0x10 (16 base)
        uint8_t index = (size >> 8) & 0xFF;
        return sizeClassTable[index] + 0x10;
    }
    else if (size != 0)
    {
        // Size 1..255: use low byte directly
        uint8_t index = size & 0xFF;
        return sizeClassTable[index];
    }
    else
    {
        // Size 0 -> error sentinel
        return 0xFFFFFFFF;
    }
}