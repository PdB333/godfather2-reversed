// FUNC_005032e0: BufferReader::readBlock
class BufferReader {
    // Members derived from param_1 offsets
    // +0x00 to +0x17: unknown
    void* m_pBuffer;       // +0x18: current read pointer (initially points to raw data)
    // +0x1C and beyond: unknown
};

typedef void (*BlockHandler)(uint32_t headerType, uint64_t id1, uint64_t id2, uint32_t subType, uint64_t dataPtrAndSize, uint32_t alignment);

struct HandlerTable {
    BlockHandler m_pHandler; // first function pointer
};

void BufferReader::readBlock(HandlerTable* handler) {
    // Save the original 4-byte value before alignment
    uint32_t headerType = *(uint32_t*)(*(uint32_t*)&m_pBuffer); // first 4 bytes of the raw pointer's content

    // Align the buffer pointer to 4-byte boundary (round down to nearest multiple of 4)
    uint8_t* alignedPtr = (uint8_t*)((uint32_t)(*(uint32_t*)&m_pBuffer) + 7U & 0xFFFFFFFC);
    m_pBuffer = alignedPtr;

    // Read packed header from aligned position
    uint64_t id1 = *(uint64_t*)(alignedPtr + 0);       // +0x00
    uint64_t id2 = *(uint64_t*)(alignedPtr + 8);       // +0x08
    uint32_t subType = *(uint32_t*)(alignedPtr + 16);  // +0x10

    // Advance read pointer past header fields
    m_pBuffer = alignedPtr + 0x14; // temporary, will overwrite

    int32_t itemCount = *(int32_t*)(alignedPtr + 0x14);   // +0x14
    m_pBuffer = alignedPtr + 0x18; // temporary

    int32_t alignmentSize = *(int32_t*)(alignedPtr + 0x18); // +0x18

    // Calculate aligned start address of the data block (relative to alignedPtr)
    // formula: (alignedPtr + alignmentSize + 0x1B) & ~(alignmentSize - 1)
    uint32_t dataStart = ((uint32_t)alignedPtr + alignmentSize + 0x1B) & ~(alignmentSize - 1U);

    // Final read pointer is set to the beginning of the next item after this block
    // Each item is 0x20 bytes, so total data size = itemCount * 0x20
    // Data start is already aligned. Next pointer = dataStart + itemCount * 0x20
    *(uint32_t*)&m_pBuffer = itemCount * 0x20 + dataStart;

    // Prepare the 64-bit argument: high 32 bits = itemCount, low 32 bits = dataStart (or 0 if itemCount == 0)
    uint64_t dataArg;
    if (itemCount != 0) {
        dataArg = ((uint64_t)itemCount << 32) | dataStart;
    } else {
        dataArg = (uint64_t)itemCount << 32; // low part = 0
    }

    // Call the handler with the parsed header fields and data descriptor
    handler->m_pHandler(headerType, id1, id2, subType, dataArg, alignmentSize);
}