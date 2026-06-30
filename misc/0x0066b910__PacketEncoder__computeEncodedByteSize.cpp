// FUNC_NAME: PacketEncoder::computeEncodedByteSize
// Function address: 0x0066b910
// Role: Computes the byte size of a packed bitstream based on count and a bitfield.
// The structure: [0] = count (number of units), [3] = pointer to array of uint32 bitfields.
// Each unit except the last contributes 28 bits; the last unit contributes popcount of its 32-bit field.
// Total bits are rounded up to nearest byte.

#include <cstdint>

int __fastcall computeEncodedByteSize(int32_t thisPtr_unused, uint32_t* bufferInfo)
{
    uint32_t count = bufferInfo[0];
    uint32_t totalBits = 0;

    if (count != 0)
    {
        // Bits from the first (count-1) units: each unit is 28 bits.
        totalBits = count * 28 - 28; // (count-1) * 28

        // The fourth field (offset 12 from bufferInfo) is a pointer to an array of uint32 bitfields.
        uint32_t* bitfieldArray = reinterpret_cast<uint32_t*>(bufferInfo[3]);

        // Read the last uint32 in the array (index count-1).
        uint32_t lastBitfield = bitfieldArray[count - 1];

        // Count set bits in the last bitfield (popcount loop).
        uint32_t bits = lastBitfield;
        while (bits != 0)
        {
            totalBits++;
            bits >>= 1;
        }
    }

    // Round up to the nearest byte: ceil(totalBits / 8)
    int32_t byteSize = (static_cast<int32_t>(totalBits) + 7) / 8;
    return byteSize;
}