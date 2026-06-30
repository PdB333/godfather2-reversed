// FUNC_NAME: BufferWriter::writeAlignedBlocks
// Address: 0x004b91f0
// Role: Serializes multiple array blocks with alignment into a memory buffer (used for packet construction)
// Field offsets: [this + 0x14] = byte* m_writePtr (current write position)

class BufferWriter {
public:
    // Data member at offset 0x14
    uint8_t* m_writePtr;   // current buffer write pointer

    // Writes three 4-byte header values, then three blocks:
    //   Block1: two ints (count1, align1) followed by count1 * 4 bytes from array1, aligned to align1
    //   Block2: two ints (count2, align2) followed by count2 * 12 bytes from array2, aligned to align2
    //   Block3: two ints (count3, align3) followed by count3 * 8 bytes from array3, aligned to align3
    //   Ends with a 2-byte value, then padding to 4-byte alignment
    void __thiscall writeAlignedBlocks(
        uint32_t header1,           // param_1
        uint32_t header2,           // param_2
        uint32_t header3,           // param_3
        const uint32_t* array1,     // param_4
        int32_t count1,             // param_5
        int32_t align1,             // param_6
        const uint8_t* array2,      // param_7    (element size 12)
        int32_t count2,             // param_8
        int32_t align2,             // param_9
        const uint64_t* array3,     // param_10   (element size 8)
        int32_t count3,             // param_11
        int32_t align3,             // param_12
        uint16_t finalValue         // param_13
    ) {
        // Write three header ints
        *(uint32_t*)m_writePtr = header1;
        m_writePtr += 4;
        *(uint32_t*)m_writePtr = header2;
        m_writePtr += 4;
        *(uint32_t*)m_writePtr = header3;
        m_writePtr += 4;

        // Block 1: metadata and array of 4-byte elements
        *(int32_t*)m_writePtr = count1;
        m_writePtr += 4;
        *(int32_t*)m_writePtr = align1;
        m_writePtr += 4;
        // Align to align1 boundary
        m_writePtr = (uint8_t*)((uintptr_t)(m_writePtr + align1 - 1) & ~(align1 - 1));
        memcpy(m_writePtr, array1, count1 * 4);
        m_writePtr += count1 * 4;

        // Block 2: metadata and array of 12-byte elements
        *(int32_t*)m_writePtr = count2;
        m_writePtr += 4;
        *(int32_t*)m_writePtr = align2;
        m_writePtr += 4;
        // Align to align2 boundary
        m_writePtr = (uint8_t*)((uintptr_t)(m_writePtr + align2 - 1) & ~(align2 - 1));
        memcpy(m_writePtr, array2, count2 * 12);
        m_writePtr += count2 * 12;

        // Block 3: metadata and array of 8-byte elements
        *(int32_t*)m_writePtr = count3;
        m_writePtr += 4;
        *(int32_t*)m_writePtr = align3;
        m_writePtr += 4;
        // Align to align3 boundary
        m_writePtr = (uint8_t*)((uintptr_t)(m_writePtr + align3 - 1) & ~(align3 - 1));
        memcpy(m_writePtr, array3, count3 * 8);
        m_writePtr += count3 * 8;

        // Write final 2-byte value and align to 4 bytes
        *(uint16_t*)m_writePtr = finalValue;
        m_writePtr += 2;
        // Round up to next 4-byte boundary (align to 4)
        m_writePtr = (uint8_t*)((uintptr_t)(m_writePtr + 3) & ~3);
    }
};