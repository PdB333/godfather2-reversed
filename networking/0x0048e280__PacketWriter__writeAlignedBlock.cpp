// FUNC_NAME: PacketWriter::writeAlignedBlock
// Address: 0x0048e280
// Role: Writes an aligned data block with header (count, alignment) and a trailing bool flag into a packet buffer.
// The object at `this` has a member at +0x14 which is a pointer to the current write pointer (byte** m_writePosPtr).
// Data is written as a series of 4-byte elements, then aligned to the specified boundary, then a bool, then aligned to 4.

#include <cstring>

class PacketWriter {
public:
    // +0x14: pointer to current write pointer (byte**)
    // The class may have other fields, but only this one is used here.
    byte** m_writePosPtr;  // Points to a byte* that indicates where to write next.

    // Write an aligned block of data.
    // @param data: Pointer to source data (array of int32-sized elements)
    // @param elementCount: Number of 4-byte elements in data
    // @param alignment: Byte alignment boundary for the data block (~(alignment-1) mask)
    // @param flag: Boolean value to write after the data block
    void writeAlignedBlock(void* data, int elementCount, int alignment, bool flag) {
        // Write element count as int32
        **(int**)m_writePosPtr = elementCount;
        *m_writePosPtr += 4;

        // Write alignment value as int32 (used later for alignment)
        **(int**)m_writePosPtr = alignment;
        *m_writePosPtr += 4;

        // Align the current write pointer to the specified boundary
        byte* dst = (byte*)((uintptr_t)(*m_writePosPtr - 1 + alignment) & ~(uintptr_t)(alignment - 1));
        *m_writePosPtr = dst;

        // Copy the data block (size = elementCount * 4 bytes)
        memcpy(dst, data, elementCount * 4);
        *m_writePosPtr += elementCount * 4;

        // Write the boolean flag at current position
        **(bool**)m_writePosPtr = flag;

        // Align pointer to next 4-byte boundary (padding for bool)
        *m_writePosPtr = (byte*)(((uintptr_t)(*m_writePosPtr) + 4) & 0xFFFFFFFC);
    }
};