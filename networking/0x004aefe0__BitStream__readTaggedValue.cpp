// FUNC_NAME: BitStream::readTaggedValue

#include <cstdint>

// BitStream class - EA EARS engine bitstream reader
// Fields:
// +0x00: unknown (likely vtable pointer)
// +0x04: unknown
// +0x08: unknown
// +0x0c: uint8_t* m_data       // pointer to raw bit data
// +0x10: unknown
// +0x14: unknown
// +0x18: uint32_t m_bitPos     // current read position in bits
// +0x1c: bool m_overflow       // overflow flag set when reading past end
// +0x20: unknown
// +0x24: unknown
// +0x28: unknown
// +0x2c: uint32_t m_totalBits  // total number of valid bits in the stream

// Output structure for a tagged value read from the stream
struct TaggedValue {
    uint32_t tag;                // +0x00 (actually stored at +0x04? The function stores at param2+4)
    void* data1;                 // +0x08
    void* data2;                 // +0x0c
    void* data3;                 // +0x10
};

// Forward declarations of helper functions (externally defined)
extern uint8_t BitStream_readByte(BitStream* thisStream);  // hypothetically at 0x0046d790
extern void* BitStream_readData(BitStream* thisStream, uint32_t size); // hypothetically at 0x0064b9e0

void BitStream::readTaggedValue(TaggedValue* outValue)
{
    uint32_t mask = 0;
    uint32_t totalBits = *(uint32_t*)(this + 0x2c);
    uint32_t bitPos;

    // Read 4 bits to form a tag mask
    for (int i = 0; i < 4; i++) {
        bitPos = *(uint32_t*)(this + 0x18);
        if (bitPos >= totalBits) {
            // Overflow: set overflow flag and skip this bit
            *(uint8_t*)(this + 0x1c) = 1;
        } else {
            // Read one bit from the stream
            uint8_t byte = *(uint8_t*)(*(uint32_t*)(this + 0x0c) + (bitPos >> 3));
            // Use bitmask to extract the bit at position (bitPos & 7)
            uint8_t bit = (byte >> (bitPos & 7)) & 1;
            if (bit) {
                mask |= (1 << i);
            }
            // Advance bit position
            *(uint32_t*)(this + 0x18) = bitPos + 1;
        }
        // Note: after overflow, bitPos stays the same, so subsequent iterations also overflow
    }

    // Store the 4-bit mask in the output structure (at offset +4? but it's stored at outValue+4)
    *(uint32_t*)(outValue + 4) = mask;

    // Based on tag, read additional data
    switch (mask) {
    case 1:
    case 7:
        // Read a 0xA0-sized block (e.g., a string or large structure)
        outValue->data1 = BitStream_readData(this, 0xA0);
        break;
    case 2:
        // Read a single byte (via a separate readByte function)
        outValue->data1 = (void*)(uintptr_t)(BitStream_readByte(this) & 0xFF);
        break;
    case 3:
    case 4:
        // Read a 0x20-sized block (e.g., a 32-byte chunk)
        outValue->data1 = BitStream_readData(this, 0x20);
        break;
    case 5:
    case 6:
        // Read two 0x20-sized blocks
        outValue->data1 = BitStream_readData(this, 0x20);
        outValue->data2 = BitStream_readData(this, 0x20);
        break;
    case 8:
        // Read three 0x20-sized blocks
        outValue->data1 = BitStream_readData(this, 0x20);
        outValue->data2 = BitStream_readData(this, 0x20);
        outValue->data3 = BitStream_readData(this, 0x20);
        break;
    default:
        // No additional data for other tag values (0, etc.)
        break;
    }
}