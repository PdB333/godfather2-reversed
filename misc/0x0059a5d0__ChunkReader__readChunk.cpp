// FUNC_NAME: ChunkReader::readChunk
void __thiscall ChunkReader::readChunk(int this)
{
    // this +0x8 points to the raw buffer
    int buffer = *(int *)(this + 8);

    // Validate header size: ushort at buffer+2 should equal (buffer->dataSize * 8 + 0x1c)
    if ((uint)*(ushort *)(buffer + 2) != *(int *)(buffer + 0x18) * 8 + 0x1cU)
    {
        // Error handler: asserts and possibly crashes
        (**(code **)(*DAT_01205590 + 4))();
    }

    // Build a chunk identifier from four bytes at offsets 4,8,0xc,0x10 (big-endian)
    uint chunkId = ((*(int *)(buffer + 4) * 0x100 + *(int *)(buffer + 8)) * 0x100 +
                    *(int *)(buffer + 0xc)) * 0x100 + *(int *)(buffer + 0x10);

    // Look up the handler for this chunk ID
    int handler = chunkHandlerLookup(this, chunkId);  // FUN_00599aa0

    if (handler == 0)
    {
        // Error handler if no handler found
        (**(code **)(*DAT_01205590 + 4))();
        return;
    }

    // Process the chunk data starting at buffer + 0x1c
    processChunkData(buffer + 0x1c);  // FUN_00594800
}

// External functions called
extern int __fastcall chunkHandlerLookup(int this, uint chunkId);
extern void __fastcall processChunkData(int dataPtr);