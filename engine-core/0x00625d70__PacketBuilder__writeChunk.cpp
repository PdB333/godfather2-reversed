// FUNC_NAME: PacketBuilder::writeChunk
void PacketBuilder::writeChunk(uint32 chunkType, int dataSize)
{
    // Check if buffer has space for header (8 bytes)
    BufferHeader* header = *(BufferHeader**)(this + 0x10);
    if (header->currentSize <= header->maxSize)
    {
        expandBuffer(); // FUN_00627360
    }

    // Allocate a data block of given size
    Block* block = (Block*)allocateBlock(dataSize); // FUN_00638110
    block->type = chunkType; // +0x0C

    // Move write pointer backward to make room for the new header
    // param_3 * -8 = dataSize * -8 (each data word is 8 bytes? Actually unknown)
    uint8* writePtr = *(uint8**)(this + 0x8);
    writePtr += dataSize * (-8); // Move back by dataSize*8 bytes
    *(uint8**)(this + 0x8) = writePtr;

    // Copy existing data from the buffer into the block
    if (dataSize != 0)
    {
        uint32* dest = (uint32*)(block + 0x10 + dataSize * 8); // end of block data area
        do
        {
            dest -= 2; // move back by 2 words (8 bytes)
            uint32* src = (uint32*)((uint8*)dest + *(int*)(this + 0x8) + (-0x10 - (int)block));
            dest[0] = src[0];
            dest[1] = src[1];
            --dataSize;
        } while (dataSize != 0);
    }

    // Write chunk header: type 6 (maybe a data chunk ID) and pointer to block
    uint32* headerOut = *(uint32**)(this + 0x8);
    headerOut[0] = 6;   // Chunk type: "data block"
    headerOut[1] = (uint32)block; // Pointer to allocated block

    // Advance write pointer by header size (8 bytes)
    *(uint8**)(this + 0x8) += 8;
}