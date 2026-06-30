// FUNC_NAME: PacketBuilder::writeArrayChunk
// Function at 0x00503410: Serializes a 20-byte header (type, two 64-bit IDs, flags), two 32-bit integers (count and alignment), and an array of 0x20-byte structures into a packet buffer. The write pointer is stored at offset +0x14 of the `PacketBuilder` object.

class PacketBuilder {
public:
    char *m_writePos; // +0x14: current write position in the buffer

    void writeArrayChunk(uint32_t headerType, uint64_t id1, uint64_t id2, uint32_t flags,
                         const void *dataArray, int32_t count, int32_t alignment)
    {
        // Write header type (4 bytes)
        *(uint32_t *)m_writePos = headerType;

        // Align to 4-byte boundary (from current position)
        m_writePos = (char *)(((uintptr_t)m_writePos + 7) & ~3U);

        // Write two 64-bit IDs
        *(uint64_t *)m_writePos = id1;
        ((uint64_t *)m_writePos)[1] = id2;

        // Write flags (4 bytes), placed after the two 8-byte fields
        *(uint32_t *)(m_writePos + 16) = flags;

        // Advance past the 20-byte header (4+16 = 20 = 0x14)
        m_writePos += 0x14;

        // Write count and alignment (8 bytes total)
        *(int32_t *)m_writePos = count;
        m_writePos += 4;
        *(int32_t *)m_writePos = alignment;
        m_writePos += 4;

        // Align pointer to the next `alignment`-byte boundary
        m_writePos = (char *)(~((uintptr_t)alignment - 1) & ((uintptr_t)m_writePos + (uintptr_t)alignment + 3));

        // Copy the array of 0x20-byte elements
        memcpy(m_writePos, dataArray, count * 0x20);

        // Advance past the array
        m_writePos += count * 0x20;
    }
};