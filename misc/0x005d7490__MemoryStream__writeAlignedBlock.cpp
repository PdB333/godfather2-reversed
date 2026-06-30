// FUNC_NAME: MemoryStream::writeAlignedBlock
// Function address: 0x005d7490
// Writes a structured block with alignment, metadata, and trailer
// The stream state contains a current write pointer at offset +0x14.

class MemoryStream {
public:
    uint8_t* m_curWritePtr; // +0x14, current position in the buffer
};

void MemoryStream::writeAlignedBlock(
    int field1,               // first metadata field (written before alignment)
    int field2,               // second metadata field
    void* data,               // raw data to copy
    size_t size,              // size of data
    int alignment,            // alignment requirement (must be power of 2)
    int trailer               // trailer value written after data
) {
    // Align current pointer to 4 bytes and write field1
    uint32_t* alignedPtr = (uint32_t*)((uintptr_t)(m_curWritePtr + 3) & ~3);
    m_curWritePtr = (uint8_t*)alignedPtr;
    *alignedPtr = field1;
    m_curWritePtr += 4;

    // Write field2 (unconditionally 4 bytes)
    *(uint32_t*)m_curWritePtr = field2;
    m_curWritePtr += 4;

    // Write size
    *(size_t*)m_curWritePtr = size;
    m_curWritePtr += 4;

    // Write alignment value
    *(int*)m_curWritePtr = alignment;
    m_curWritePtr += 4;

    // Align to the specified alignment (e.g., for SSE or cache line)
    uint8_t* alignedData = (uint8_t*)((uintptr_t)(m_curWritePtr + alignment - 1) & ~(alignment - 1));
    m_curWritePtr = alignedData;

    // Copy the data block
    memcpy(m_curWritePtr, data, size);

    // Advance pointer rounded up to 4-byte boundary
    m_curWritePtr += (size + 3) & ~3;

    // Write trailer
    *(uint32_t*)m_curWritePtr = trailer;
    m_curWritePtr += 4;
}