// FUNC_NAME: PacketReader::readAndDispatch
void PacketReader::readAndDispatch(PacketReader *this, void *funcTable) {
    // this+0x18 holds a pointer to the current read position in a buffer
    char *readPtr = *(char **)(this + 0x18);
    // Align the read pointer to next 4-byte boundary (round up)
    char *alignedPtr = (char *)(((int)readPtr + 7) & 0xFFFFFFFC);
    *(char **)(this + 0x18) = alignedPtr;

    // Read 32-byte header block
    char headerBlock[32];
    _memcpy(headerBlock, alignedPtr, 32);
    *(char **)(this + 0x18) = alignedPtr + 32;

    // Read 4-byte value at offset 0x20
    int value32bit1 = *(int *)(alignedPtr + 32);
    *(char **)(this + 0x18) = alignedPtr + 36;

    // Read 8-byte value at offset 0x24
    __int64 value64 = *(__int64 *)(alignedPtr + 36);
    *(char **)(this + 0x18) = alignedPtr + 44;

    // Read 4-byte value at offset 0x2c
    int value32bit2 = *(int *)(alignedPtr + 44);
    *(char **)(this + 0x18) = alignedPtr + 48;

    // Decompose 64-bit value into low and high parts
    int lowPart = (int)value64;
    int highPart = (int)(value64 >> 32);

    // Call the handler function (first entry in funcTable) with the extracted data
    // handler(getBufferStart??, headerBlock (as four 8-byte chunks), value32bit1, lowPart, highPart, value32bit2)
    void (*handler)(int, __int64, __int64, __int64, __int64, int, int, int, int) = *(void (**)(void))funcTable;
    handler(*(int *)(*(int *)(this + 0x18)),       // probably the original buffer start
            *(__int64 *)&headerBlock[0],           // headerBlock[0..7]
            *(__int64 *)&headerBlock[8],           // headerBlock[8..15]
            *(__int64 *)&headerBlock[16],          // headerBlock[16..23]
            *(__int64 *)&headerBlock[24],          // headerBlock[24..31]
            value32bit1,
            lowPart,
            highPart,
            value32bit2);
}