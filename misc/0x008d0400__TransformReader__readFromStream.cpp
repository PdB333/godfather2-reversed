// FUNC_NAME: TransformReader::readFromStream
void __thiscall TransformReader::readFromStream(int this, Stream* stream) {
    // Begin reading data block with marker 0x3e8bf7b3
    stream->beginBlock(0x3e8bf7b3);

    while (!stream->isEndOfBlock()) {
        Chunk* chunk = stream->readNextChunk();
        int chunkType = chunk->getType();

        if (chunkType == 0) {
            // Process chunk type 0: reads a sub-stream into a buffer
            int buffer = this + 0x78;
            stream->readNextChunk(buffer);
            chunk->processType0(buffer);
        } else if (chunkType == 1) {
            // Chunk type 1: store square of value[2] at offset 0x70
            Chunk* chunk2 = stream->readNextChunk();
            *(float*)(this + 0x70) = *(float*)(chunk2 + 8) * *(float*)(chunk2 + 8);
        } else if (chunkType == 2) {
            // Chunk type 2: store square of value[2] at offset 0x74
            Chunk* chunk2 = stream->readNextChunk();
            *(float*)(this + 0x74) = *(float*)(chunk2 + 8) * *(float*)(chunk2 + 8);
        }

        stream->advanceChunk();
    }

    // End data block with marker 0xb390b11a
    stream->endBlock(0xb390b11a);
    stream->setMode(1);

    if (!stream->isEndOfBlock()) {
        // Read extra transform data: quaternion (8 bytes) and one float (4 bytes)
        TransformData localData;  // 12 bytes total? Actually layout: local_120[12], local_114, local_104, local_f4, local_f0 (8), local_e8 (4), local_e4 (4)
        // Initialize some fields
        localData.unknown1 = 0;  // local_114
        localData.unknown2 = 0;  // local_104
        localData.unknown3 = 0;  // local_f4
        localData.defaultScale = _DAT_00d5780c;  // local_e4: some global default

        // Read into local buffer
        void* buffer = &localData;  // local_120
        stream->readNextChunk(buffer);
        chunk->applyTransform(buffer);

        // Copy results to this
        *(Vector4*)(this + 0x64) = localData.quaternion;  // local_f0: 8 bytes
        *(float*)(this + 0x6c) = localData.radius;        // local_e8: 4 bytes
    }

    // Check if any bounding box extents are non-zero, set flag if so
    int* extents = (int*)(this + 0x78);
    if (extents[0] != 0 || extents[1] != 0 || extents[2] != 0 || extents[3] != 0) {
        *(int*)(this + 0x60) |= 0x10000000;
    }

    // Cleanup stream
    stream->destroy();
}