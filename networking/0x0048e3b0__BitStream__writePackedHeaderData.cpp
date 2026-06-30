// FUNC_NAME: BitStream::writePackedHeaderData

// Reconstructed from 0x0048e3b0
// Writes a 64-byte header, a size word, an alignment requirement, and then data aligned accordingly.
// The buffer pointer is stored at this+0x14.
// The initial buffer pointer is aligned to 4-byte boundary before writing the header.
// After writing header, size, and alignment value, the buffer is aligned to a multiple of alignmentValue + 3? 
// (alignment macro: (bufPtr + alignmentValue + 3) & ~(alignmentValue - 1))
// Then the data is copied with the given size.

struct __declspec(align(4)) PacketHeader {
    uint8_t data[0x40];  // 64-byte header
};

class BitStream {
public:
    // Writes a packed header and data block
    void writePackedHeaderData(const PacketHeader& header, size_t dataSize, int alignmentValue, const void* data) {
        uint8_t*& bufPtr = *(uint8_t**)(this + 0x14); // buffer write cursor

        // Align current pointer to 4 bytes
        uint8_t* aligned = (uint8_t*)((uint32_t)bufPtr + 3 & ~3);
        bufPtr = aligned;

        // Copy the 64-byte header directly from the stack (passed by value)
        memcpy(bufPtr, &header, 0x40);
        bufPtr += 0x40;

        // Write the data size
        *(size_t*)bufPtr = dataSize;
        bufPtr += 4;

        // Write the alignment value
        *(int*)bufPtr = alignmentValue;
        bufPtr += 4;

        // Align buffer pointer: (bufPtr + alignmentValue + 3) & ~(alignmentValue - 1)
        bufPtr = (uint8_t*)((uint32_t)bufPtr + alignmentValue + 3 & ~(alignmentValue - 1));

        // Copy the actual data
        memcpy(bufPtr, data, dataSize);
        bufPtr += (dataSize + 3 & ~3); // align to 4 bytes after data
    }
};