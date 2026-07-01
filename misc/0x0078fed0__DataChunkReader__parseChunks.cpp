// FUNC_NAME: DataChunkReader::parseChunks
// Address: 0x0078fed0
// Role: Reads a sequence of typed chunks from a binary stream, storing values at offsets 0xD0 and 0xC8.

void __thiscall DataChunkReader::parseChunks(void* this, uint32_t dataIdentifier)
{
    // Initialize the chunk reader with a hash (likely CRC or magic)
    beginRead(dataIdentifier, 0x55859efa);

    // Loop until all chunks are processed
    while (!isEndOfChunks())
    {
        // Get the next chunk pointer
        void* chunk = readNextChunk();

        // Determine chunk type
        int32_t chunkType = getChunkType();

        if (chunkType == 1)
        {
            // For type 1, read another chunk and store its value at offset 0xD0
            void* valueChunk = readNextChunk();
            *(uint32_t*)((uint8_t*)this + 0xD0) = *(uint32_t*)((uint8_t*)valueChunk + 8);
        }
        else if (chunkType == 2)
        {
            // For type 2, read another chunk and store its value at offset 0xC8
            void* valueChunk = readNextChunk();
            *(uint32_t*)((uint8_t*)this + 0xC8) = *(uint32_t*)((uint8_t*)valueChunk + 8);
        }

        // Advance to the next chunk in the sequence
        advanceToNextChunk();
    }
}