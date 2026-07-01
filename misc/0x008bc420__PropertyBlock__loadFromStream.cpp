// FUNC_NAME: PropertyBlock::loadFromStream
// Address: 0x008bc420
// This function reads a property block from a chunked stream. It expects a stream initialized with a magic (0x129f7657).
// It loops reading tagged entries: 0 = int (offset +0x50), 1 = string (offset +0x54), 2 = int (offset +0x5c),
// 3 = Vector4 (four floats/ints at offsets +0x60 through +0x6c).

void PropertyBlock::loadFromStream(StreamReader &stream) // __thiscall
{
    // Initialize stream and verify chunk magic
    stream.beginRead();
    stream.readMagic(0x129f7657);

    // Process entries until end-of-data flag is set
    while (!stream.isEnd())
    {
        stream.beginEntry();

        uint32_t entryType = stream.readEntryType();
        switch (entryType)
        {
        case 0: // int32 at +0x50
        {
            // read integer from stream (probably an index or resource ID)
            stream.readNext();
            int value = stream.readInt();
            *(int *)(this + 0x50) = value;
            break;
        }
        case 1: // string at +0x54
        {
            stream.readNext();
            const char *str = stream.readString();
            stringCopy((char *)(this + 0x54), str); // copies the string to field
            break;
        }
        case 2: // int32 at +0x5c
        {
            stream.readNext();
            int value = stream.readInt();
            *(int *)(this + 0x5c) = value;
            break;
        }
        case 3: // Vector4 (4 floats/ints) at +0x60, +0x64, +0x68, +0x6c
        {
            stream.readNext();
            const float *vec = stream.readFloatArray(); // returns pointer to 4 floats
            *(float *)(this + 0x60) = vec[0]; // X
            *(float *)(this + 0x64) = vec[1]; // Y
            *(float *)(this + 0x68) = vec[2]; // Z
            *(float *)(this + 0x6c) = vec[3]; // W
            break;
        }
        }

        stream.endEntry();
    }
}