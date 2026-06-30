// FUNC_NAME: PacketWriter::writeAlignedBlock

#include <cstring>  // for memcpy

struct PacketWriter {
    // The current write position in the buffer; offset +0x14 in the structure
    uint32_t* mWritePos;
};

void PacketWriter::writeAlignedBlock(
    uint32_t type,
    uint32_t subtype,
    size_t dataSize,
    const void* data,
    uint32_t alignment,
    uint32_t footer)
{
    // Append the block header fields sequentially (each 4 bytes)
    *mWritePos++ = type;
    *mWritePos++ = subtype;
    *mWritePos++ = dataSize;
    *mWritePos++ = alignment;

    // Align the destination pointer to the given alignment
    // ~(alignment - 1) masks off the lower bits to align down
    uint32_t alignedOffset = ~(alignment - 1U) & (alignment + 3 + reinterpret_cast<uint32_t>(mWritePos));
    mWritePos = reinterpret_cast<uint32_t*>(alignedOffset);

    // Copy the actual data block
    memcpy(mWritePos, data, dataSize);

    // Advance the write pointer by the aligned size of the data
    uint32_t alignedDataSize = (dataSize + 3) & 0xFFFFFFFC;
    mWritePos = reinterpret_cast<uint32_t*>(reinterpret_cast<uint32_t>(mWritePos) + alignedDataSize);

    // Write the footer
    *mWritePos++ = footer;
}