// FUNC_NAME: MemoryStream::writeAlignedData
// Address: 0x005cbe70
// Role: Writes an aligned array of 24-byte structures followed by a 64-byte block into a memory stream buffer.
// The stream's current write pointer is stored at offset +0x14 (int* m_writePos).
// param_1: source array of structures (each 0x18 bytes)
// param_2: number of elements in the array
// param_3: alignment boundary for the array (e.g., 4, 8, 16)
// param_4: source 64-byte block to write after the array

class MemoryStream {
public:
    int* m_writePos; // +0x14: pointer to current write position in buffer

    void __thiscall writeAlignedData(const void* array, int count, int alignment, const void* block) {
        // Write count and alignment as two consecutive ints
        *m_writePos = count;
        m_writePos++;
        *m_writePos = alignment;
        m_writePos++;

        // Align the write pointer to the specified alignment for the array
        m_writePos = (int*)(((int)m_writePos - 1 + alignment) & ~(alignment - 1));

        // Copy the array of count * 0x18 bytes
        memcpy(m_writePos, array, count * 0x18);

        // Align to 16-byte boundary for the block
        m_writePos = (int*)(((int)m_writePos + count * 0x18 + 0xF) & ~0xF);

        // Copy the 64-byte block
        memcpy(m_writePos, block, 0x40);

        // Advance write pointer past the block
        m_writePos = (int*)((char*)m_writePos + 0x40);
    }
};