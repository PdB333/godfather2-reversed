// FUNC_NAME: PacketBuilder::writeDataBlock

void __thiscall PacketBuilder::writeDataBlock(int *this, uint32_t typeId, uint64_t data0, uint64_t data1, uint64_t data2, uint64_t data3)
{
    // this: pointer to PacketBuilder object; first field (offset 0x00) is a pointer to a Stream object
    int *streamPtr = (int *)*this;          // +0x00: stream pointer
    int *writeCursor = (int *)streamPtr[5]; // +0x14: current write position in stream

    // Write virtual table / type identifier (4 bytes)
    *(void **)writeCursor = (void *)&PTR_FUN_01124cec;
    writeCursor += 1; // advance past vtable pointer

    // Write the 4-byte type ID
    *(uint32_t *)writeCursor = typeId;
    writeCursor += 1;

    // Align to next 4-byte boundary (round up to multiple of 4)
    writeCursor = (int *)(((uint32_t)writeCursor + 7) & ~3);

    // Copy the 32-byte data block (4 x uint64 = 32 bytes)
    uint8_t dataBlock[32];
    *(uint64_t *)&dataBlock[0]  = data0;
    *(uint64_t *)&dataBlock[8]  = data1;
    *(uint64_t *)&dataBlock[16] = data2;
    *(uint64_t *)&dataBlock[24] = data3;
    _memcpy(writeCursor, dataBlock, 32);

    // Update the stream's write cursor
    streamPtr[5] = (int)(writeCursor + 8); // +32 bytes / sizeof(int) = 8 ints
}