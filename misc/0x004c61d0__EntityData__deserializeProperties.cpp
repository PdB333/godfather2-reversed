// FUNC_NAME: EntityData::deserializeProperties

void __thiscall EntityData::deserializeProperties(EntityData* this, SerializationStream* stream)
{
    // Local variables used for iteration over serialized chunks
    bool isIndexed;           // local_78 - mode flag (indexed vs pointer-based)
    int* ptrCurrentChunk;     // local_1c
    int currentIndex;         // local_6c
    int maxIndex;             // local_68
    uint** chunkArray;        // local_94
    uint* currentChunk;       // local_dc
    uint* nextChunkPtr;       // local_e8
    uint chunkCount;          // local_e4
    uint totalChunks;         // local_e0
    uint keyValue;            // puVar1 - the key from the chunk
    uint local_d4, local_d0, local_cc, local_c8, local_c4; // temporary data

    // Begin reading a block with magic 0xb390b11a
    stream->beginBlock(0xb390b11a);
    stream->allocateChunks(1); // allocate one chunk

    // Check if the stream uses indexed or pointer-based chunk references
    if (isIndexed == 0) {
        // Pointer mode: check if first chunk is null
        if (*ptrCurrentChunk == 0) {
            return; // nothing to read
        }
    } else {
        // Indexed mode: check if current index >= max index
        if (currentIndex >= maxIndex) {
            return;
        }
    }

    // Initialize output fields to defaults
    local_d4 = 0;
    local_c4 = 0;
    // DAT_00e2b1a4 is likely a global default value (e.g., identity quaternion)
    local_b4 = DAT_00e2b1a4;
    stream->readVector(local_f0); // reads a 4-component vector into local buffer

    // Copy vector into object at offsets 0x50-0x5c (position/rotation?)
    this->field_0x50 = local_d0;
    this->field_0x54 = local_cc;
    this->field_0x58 = local_c8;
    this->field_0x5c = local_d4; // fourth component (maybe w of quaternion)

    // Clear the "dirty" flag at offset 0x68
    this->field_0x68 &= 0x7fffffff;

    // End current block and begin a new one with magic 0x531ded0
    stream->endBlock(0xb390b11a);
    stream->beginBlock(0x531ded0);

    // Iterate over all chunks in the stream
    while (true) {
        if (isIndexed == 0) {
            if (*chunkArray == 0) break; // null terminator
        } else {
            if (chunkCount >= totalChunks) break; // index out of range
        }

        // Determine which chunk pointer to use (indexed or direct)
        uint** currentChunkPtr;
        if (isIndexed == 0) {
            currentChunkPtr = chunkArray;
        } else {
            currentChunkPtr = &currentChunk;
        }

        // Read key from chunk: if type byte at offset +6 equals 0x25e3 (9699),
        // then key is a ushort from offset +4, otherwise it's a pointer from offset +4
        uint key;
        if (*(short*)((int)currentChunkPtr + 6) == 0x25e3) {
            key = (uint)*(ushort*)(currentChunkPtr + 1); // ushort key
        } else {
            key = (uint)currentChunkPtr[1]; // pointer key
        }

        // Set object fields based on key value (0, 1, 2)
        uint* dataPtr;
        if (key == 0) {
            // Key 0: set field at offset 0x60
            dataPtr = currentChunkPtr[2];
            this->field_0x60 = dataPtr;
        } else if (key == 1) {
            // Key 1: set field at offset 0x64 (100 decimal)
            dataPtr = currentChunkPtr[2];
            this->field_0x64 = dataPtr;
        } else if (key == 2) {
            // Key 2: set field at offset 0x68
            dataPtr = currentChunkPtr[2];
            this->field_0x68 = dataPtr;
        }

        // Advance to next chunk
        if (isIndexed == 0) {
            // Pointer mode: move to next chunk by adding offset from current chunk
            chunkArray = (uint**)((int)chunkArray + (int)*chunkArray);
            stream->checkNext(); // internal iterator advance
            chunkCount = chunkCount; // not updated consistently
        } else {
            // Indexed mode: increment index
            chunkCount++;
            if (chunkCount != totalChunks) {
                // Read next chunk from stream if available
                currentChunk->d8 = (short)chunkCount; // store index
                if ((*(byte*)((chunkCount >> 3) + currentIndex) & (1 << (chunkCount & 7))) == 0) {
                    // Chunk present in stream
                    currentChunk = nextChunkPtr;
                    currentChunk->d4 = *nextChunkPtr;
                    nextChunkPtr++;
                } else {
                    // Chunk not present
                    currentChunk = 0;
                    currentChunk->d4 = 0;
                }
            }
        }
    }
}