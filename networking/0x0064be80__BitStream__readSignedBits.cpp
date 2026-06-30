// FUNC_NAME: BitStream::readSignedBits

#include <stdint.h>

// Helper function: reads numBits bits from the bitstream into *out
// Defined elsewhere (at 0x0064b9e0)
void __thiscall BitStream::readBits(uint8 numBits, uint* out);

// Reads a signed value from the bitstream using fixed-length encoding.
// numBits includes the sign bit.
// Returns the decoded signed integer.
int __thiscall BitStream::readSignedBits(uint8 numBits) {
    // Bitstream state:
    // +0x0c: pointer to byte buffer (bitData)
    // +0x18: current bit index (readBitIndex)
    // +0x2c: total bits in buffer (totalBits)
    // +0x1c: overflow flag (set when read beyond totalBits)

    uint readBitIndex = *(uint*)(this + 0x18);
    uint totalBits = *(uint*)(this + 0x2c);
    uint8* bitData = *(uint8**)(this + 0x0c);
    uint8& overflowFlag = *(uint8*)(this + 0x1c);

    if (totalBits < readBitIndex) {
        // No more bits available
        overflowFlag = 1;
    } else {
        // Read the sign bit (1 = negative)
        uint byteIndex = readBitIndex >> 3;
        uint bitOffset = readBitIndex & 7;
        uint8 currentByte = bitData[byteIndex];

        // Advance bit index by 1
        *(uint*)(this + 0x18) = readBitIndex + 1;

        // Check sign bit
        if ((currentByte >> bitOffset) & 1) {
            // Negative value: read magnitude bits and negate
            uint8 magnitudeBits = numBits - 1;
            uint magnitude = 0;
            readBits(magnitudeBits, &magnitude);

            if (magnitudeBits == 0x20) {
                return -((int)magnitude);
            }
            // Mask and negate (mask uses lower 5 bits of magnitudeBits)
            uint mask = (1 << (magnitudeBits & 0x1f)) - 1;
            return -((int)(mask & magnitude));
        }
        // If sign bit was 0, fall through to read positive magnitude
    }

    // Read positive magnitude (or still attempt after overflow)
    uint8 magnitudeBits = numBits - 1;
    uint magnitude = 0;
    readBits(magnitudeBits, &magnitude);

    if (magnitudeBits == 0x20) {
        return (int)magnitude;
    }
    uint mask = (1 << (magnitudeBits & 0x1f)) - 1;
    return (int)(mask & magnitude);
}