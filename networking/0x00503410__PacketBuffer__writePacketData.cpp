// FUNC_NAME: PacketBuffer::writePacketData
// Address: 0x00503410
// This function writes a packet header and data into a buffer managed by the PacketBuffer class.
// The buffer pointer is stored at offset 0x14 in the class instance.
// The header consists of: a 4-byte type, two 8-byte timestamps, a 4-byte extra field,
// then a 4-byte count and 4-byte alignment, followed by an array of 32-byte blocks.
void PacketBuffer::writePacketData(int packetType, unsigned long long timestampLow, unsigned long long timestampHigh, int extraFlags, const void* dataBlocks, int blockCount, int alignment)
{
    // Write packet type (4 bytes)
    *(int*)m_writePtr = packetType;
    m_writePtr += 4;

    // Write two 64-bit timestamp values (16 bytes total)
    *(unsigned long long*)m_writePtr = timestampLow;
    m_writePtr += 8;
    *(unsigned long long*)m_writePtr = timestampHigh;
    m_writePtr += 8;

    // Write extra flags (4 bytes)
    *(int*)m_writePtr = extraFlags;
    m_writePtr += 4;

    // Write block count and alignment (8 bytes)
    *(int*)m_writePtr = blockCount;
    m_writePtr += 4;
    *(int*)m_writePtr = alignment;
    m_writePtr += 4;

    // Align pointer to the next multiple of 'alignment' (assumed power of two, typical 32)
    // Equivalent to: m_writePtr = (unsigned char*)(((int)m_writePtr + alignment - 1) & ~(alignment - 1));
    // But original uses: (~(alignment - 1)) & (alignment + 3 + m_writePtr)
    // This works when alignment is a power of two >= 4.
    m_writePtr = (unsigned char*)((~(alignment - 1)) & (alignment + 3 + (int)m_writePtr));

    // Copy blockCount * 32 bytes of data (each block is 32 bytes)
    memcpy(m_writePtr, dataBlocks, blockCount * 0x20);
    m_writePtr += blockCount * 0x20;
}