// FUNC_NAME: lzDecodeMatchOffset
// Address: 0x00652840
// This function decodes a match offset from a compressed bitstream.
// It uses two implicit register parameters: ecx = current position, edi = base offset.
// Returns the absolute match offset (base offset + decoded distance).
// The encoding uses a variable-length bit count determined by the distance value.

// Forward declaration of the bit reading function (FUN_0064b9e0)
extern void __fastcall readBits(int bitCount, int* outValue);

static int __fastcall lzDecodeMatchOffset(int currentPos, int baseOffset)
{
    // distancePlus1 = (currentPos - baseOffset) + 1
    uint distancePlus1 = (currentPos - baseOffset) + 1;

    // Compute number of bits needed to represent distancePlus1 using float exponent.
    // Convert to float; if negative (due to large unsigned), add 2^32 as float.
    float fVal = (float)(int)distancePlus1;
    if ((int)distancePlus1 < 0)
    {
        fVal += 4294967296.0f; // 2^32
    }

    // Extract exponent from float representation (biased by 127).
    uint exponent = (*(uint*)&fVal >> 23) & 0xFF;

    // bitCount = ((currentPos - baseOffset & distancePlus1) != 0) + (exponent - 127)
    // This gives the number of bits to read: floor(log2(distancePlus1)) for powers of two,
    // floor(log2(distancePlus1)) + 1 otherwise.
    uint bitCount = ((currentPos - baseOffset & distancePlus1) != 0) - 0x7F + exponent;

    // Read that many bits from the bitstream into decodedValue.
    int decodedValue = 0;
    readBits(bitCount & 0xFF, &decodedValue);

    // Compute final match offset.
    if ((bitCount & 0xFF) == 0x20) // 32 bits: direct value
    {
        return decodedValue + baseOffset;
    }
    else
    {
        // Mask to only the lower bitCount bits (though decodedValue already holds those bits)
        uint mask = (1 << (bitCount & 0x1F)) - 1;
        return (mask & decodedValue) + baseOffset;
    }
}