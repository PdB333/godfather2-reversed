// FUN_0064bc00: BitStream::reserveBits
void BitStream::reserveBits(int bitCount) {
    uint newByteSize;
    uint alignedByteSize;

    alignedByteSize = 0;
    // Compute aligned byte size from bit count (10 bits per unit? Or maybe 10 is a flag)
    // FUN_0064b9e0 likely calculates required bytes for N bits, aligned to 1024-byte boundary
    FUN_0064b9e0(bitCount, &alignedByteSize);
    alignedByteSize &= 0x3ff; // Mask to 10 bits? Actually 0x3ff = 1023, so keeps lower 10 bits? Might be alignment to 1024

    // Ensure we own the buffer (allocate a private copy if not)
    if (!m_bOwns) {
        void* newData = malloc(m_capacity);
        memcpy(newData, m_pData, m_capacity);
        m_pData = newData;
        m_bOwns = true;
    }

    // Reallocate if needed
    if (m_capacity < alignedByteSize) {
        if (m_bOwns) {
            m_capacity = alignedByteSize;
            m_pData = realloc(m_pData, alignedByteSize);
        }
    } else {
        m_capacity = alignedByteSize;
    }

    // Initialize the bit buffer for the new byte size (bits = bytes * 8)
    FUN_0064b9e0(alignedByteSize * 8, m_pData);
}