// FUNC_NAME: AnimationData::loadFromArchive
void __thiscall AnimationData::loadFromArchive(void* this, void* archive)
{
    char isDone;
    uint32_t localBuffer[30]; // used for reading byte data

    // Open the archive for reading
    openArchive(archive);
    beginReadChunk(archive, 0xe113a0f7); // magic header for this data

    // Loop while there are more chunks
    while (true)
    {
        isDone = isArchiveDone();
        if (isDone != 0)
            break;

        // Advance to next chunk
        advanceChunk();

        uint32_t chunkType = getChunkType();
        switch (chunkType)
        {
        case 0:
        {
            // Read pointer to something +0x08 into this+0x4c
            void* chunkData = readNextChunk();
            *reinterpret_cast<void**>(static_cast<char*>(this) + 0x4c) = *reinterpret_cast<void**>(static_cast<char*>(chunkData) + 8);
            break;
        }
        case 1:
        {
            // Read pointer to something +0x08 into this+0x50
            void* chunkData = readNextChunk();
            *reinterpret_cast<void**>(static_cast<char*>(this) + 0x50) = *reinterpret_cast<void**>(static_cast<char*>(chunkData) + 8);
            break;
        }
        case 2:
        {
            // Read pointer to something +0x08 into this+0x54
            void* chunkData = readNextChunk();
            *reinterpret_cast<void**>(static_cast<char*>(this) + 0x54) = *reinterpret_cast<void**>(static_cast<char*>(chunkData) + 8);
            break;
        }
        case 3:
        {
            // Read raw 4-byte RGBA color data (packed as uint8)
            void* chunkData = readNextChunk(localBuffer);
            readChunkData(localBuffer);

            // Extract individual bytes from the packed uint32
            uint32_t packed = localBuffer[0];
            float r = static_cast<float>(packed & 0xFF);
            float g = static_cast<float>((packed >> 8) & 0xFF);
            float b = static_cast<float>((packed >> 16) & 0xFF);
            float a = static_cast<float>((packed >> 24) & 0xFF);

            // Scale to [0,1] range using a global conversion factor
            float scale = DAT_00e44640;
            *reinterpret_cast<float*>(static_cast<char*>(this) + 0x60) = r * scale;
            *reinterpret_cast<float*>(static_cast<char*>(this) + 0x64) = g * scale;
            *reinterpret_cast<float*>(static_cast<char*>(this) + 0x68) = b * scale;
            *reinterpret_cast<float*>(static_cast<char*>(this) + 0x6c) = a * scale;
            break;
        }
        }
    }

    return;
}