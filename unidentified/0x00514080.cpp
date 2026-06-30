// FUN_00514080: StreamWriter::writeAlignedBuffer
void StreamWriter::writeAlignedBuffer(int type, void* data, int elementCount, int alignment)
{
    // Structure: this pointer (ESI) has a write position at +0x14
    uint8_t*& writePos = *(uint8_t**)(this + 0x14); // current pointer in buffer

    // Write type identifier
    *(int*)writePos = type;
    writePos += 4;

    // Write element count
    *(int*)writePos = elementCount;
    writePos += 4;

    // Write alignment or some parameter (possibly stride)
    *(int*)writePos = alignment;
    writePos += 4;

    // Align the write position: (current + alignment + 3) & ~(alignment - 1)
    // This effectively rounds up to the next multiple of 'alignment', but with an extra +3 offset.
    // Could be a custom padding scheme or a decompiler artifact.
    uint32_t currentAddr = (uint32_t)writePos;
    uint32_t alignedAddr = (currentAddr + alignment + 3) & ~(alignment - 1);
    writePos = (uint8_t*)alignedAddr;

    // Copy the actual data (each element is 8 bytes)
    size_t copySize = elementCount * 8;
    memcpy(writePos, data, copySize);
    writePos += copySize;
}