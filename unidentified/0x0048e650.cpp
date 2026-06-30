// FUNC_0048e650: PacketWriter::writeAlignedBlock
void PacketWriter::writeAlignedBlock(uint64_t packetId, const char header[32], size_t dataSize, int alignment, const void* data)
{
    // Align current write pointer to 4 bytes and store the 8-byte packet ID
    m_writePtr = reinterpret_cast<char*>((reinterpret_cast<uintptr_t>(m_writePtr) + 3) & ~3U);
    *reinterpret_cast<uint64_t*>(m_writePtr) = packetId;

    // Advance to next aligned position (add 11 then mask to 4-byte boundary, effectively skipping 16 bytes from previous write)
    m_writePtr = reinterpret_cast<char*>((reinterpret_cast<uintptr_t>(m_writePtr) + 11) & ~3U);
    // Copy the 32-byte header (passed by value on the stack)
    memcpy(m_writePtr, header, 32);
    m_writePtr += 32;

    // Write the data size and alignment requirement
    *reinterpret_cast<size_t*>(m_writePtr) = dataSize;
    m_writePtr += 4;
    *reinterpret_cast<int*>(m_writePtr) = alignment;
    m_writePtr += 4;

    // Align data pointer: computes (m_writePtr + alignment + 3) & ~(alignment - 1)
    // This aligns to the next multiple of 'alignment', but with an extra offset of 3 bytes
    m_writePtr = reinterpret_cast<char*>(
        (reinterpret_cast<uintptr_t>(m_writePtr) + alignment + 3) & ~(static_cast<uintptr_t>(alignment) - 1)
    );

    // Copy the actual data buffer
    memcpy(m_writePtr, data, dataSize);

    // Advance pointer past the data, aligning to 4 bytes
    m_writePtr += (dataSize + 3) & ~3U;
}