// FUNC_NAME: Node::deserialize
void __thiscall Node::deserialize(int thisPtr, void* stream)
{
    uint rawFlags;
    char isEnd;
    uint chunkType;
    int chunkData;
    uint bitmask;
    uint tableIndex;

    streamInit(stream);                         // Initialize stream reader
    streamReadMagic(stream, 0xcc6d6b17);        // Verify magic number/header

    isEnd = streamIsEnd(stream);                 // Check end-of-stream flag
    while (isEnd == '\0') {
        chunkData = streamReadNextChunk(stream); // Get next data chunk
        chunkType = streamReadChunkType(stream); // Read type of chunk

        switch (chunkType) {
        case 0:                                 // Type 0: string/settings field A
            streamReadNextChunk(stream);
            chunkData = streamReadInt(stream);
            setStringField(thisPtr + 0x58, chunkData); // +0x58: first string/pointer member
            break;
        case 1:                                 // Type 1: string/settings field B
            streamReadNextChunk(stream);
            chunkData = streamReadInt(stream);
            setStringField(thisPtr + 0x60, chunkData); // +0x60: second string/pointer member
            break;
        case 2:                                 // Type 2: raw flags (bitmask → packed flags)
            chunkData = streamReadNextChunk(stream);
            bitmask = *(uint*)(chunkData + 8);  // Read 32-bit flag mask from chunk
            *(uint*)(thisPtr + 0x50) = bitmask; // +0x50: raw 32-bit flag storage
            *(ushort*)(thisPtr + 0x54) = 0;     // +0x54: packed 16-bit flags, cleared first

            if ((bitmask & 0xFFFF) != 0) {      // Only process if low bits present
                tableIndex = 0;
                do {
                    // Lookup tables at DAT_00e54708, DAT_00e5470c, etc.
                    // Each pair: [4-byte mask] + [2-byte flag] for that mask
                    if ((*(uint*)((int)&g_flagsTable1 + tableIndex) & bitmask) != 0) {
                        *(ushort*)(thisPtr + 0x54) |=
                            *(ushort*)((int)&g_flagsTable1Flags + tableIndex);
                    }
                    if ((*(uint*)((int)&g_flagsTable2 + tableIndex) & bitmask) != 0) {
                        *(ushort*)(thisPtr + 0x54) |=
                            *(ushort*)((int)&g_flagsTable2Flags + tableIndex);
                    }
                    if ((*(uint*)((int)&g_flagsTable3 + tableIndex) & bitmask) != 0) {
                        *(ushort*)(thisPtr + 0x54) |=
                            *(ushort*)((int)&g_flagsTable3Flags + tableIndex);
                    }
                    if ((*(uint*)((int)&g_flagsTable4 + tableIndex) & bitmask) != 0) {
                        *(ushort*)(thisPtr + 0x54) |=
                            *(ushort*)((int)&g_flagsTable4Flags + tableIndex);
                    }
                    tableIndex += 0x20;
                } while (tableIndex < 0x80);    // 4 tables × 32 entries (0x20 bytes each)
            }
            break;
        case 3:                                 // Type 3: integer value
            chunkData = streamReadNextChunk(stream);
            *(uint*)(thisPtr + 0x68) = *(uint*)(chunkData + 8); // +0x68: additional integer field
            break;
        }

        streamReadNextChunk(stream);             // Advance to next chunk
        isEnd = streamIsEnd(stream);
    }
    return;
}