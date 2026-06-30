// FUNC_NAME: PropertyBlock::readFromStream
// Function address: 0x006ab580
// Role: Deserializes a property block from a binary stream, parsing tokenized fields into member variables.
// Fields at offsets: +0x50 (string), +0x58 (string), +0x60 (string), +0x78 (short), +0x7a (short), +0x7c (short),
// +0x80 (float), +0x84 (float), +0x98 (bool), +0x99 (bool).

void __thiscall PropertyBlock::readFromStream(int thisPtr, int streamHandle)
{
    // Initialize the stream with a magic identifier
    streamBegin(streamHandle);
    streamSetMagic(streamHandle, 0xe38005b9);  // EARS engine magic constant

    bool hasMore = streamHasMoreData();
    while (!hasMore)
    {
        // Advance to next data token
        int tokenNode = streamReadNext();      // returns pointer to token structure

        int tokenType = streamReadTokenType(); // returns 0-10
        switch (tokenType)
        {
        case 0:
        {
            streamReadNext();
            const char* strVal = streamReadString();
            setStringField((void*)(thisPtr + 0x50), strVal); // +0x50: first string property
            break;
        }
        case 1:
        {
            streamReadNext();
            const char* strVal = streamReadString();
            setStringField((void*)(thisPtr + 0x58), strVal); // +0x58: second string property
            break;
        }
        case 2:
        {
            streamReadNext();
            const char* strVal = streamReadString();
            processStringProperty(strVal); // unknown action (e.g., parsing or execution)
            break;
        }
        case 3:
        {
            int node = streamReadNext();
            bool boolVal = *(int*)(node + 8) != 0;
            *(bool*)(thisPtr + 0x99) = boolVal; // +0x99: first bool property
            break;
        }
        case 4:
        {
            int node = streamReadNext();
            short shortVal = *(short*)(node + 8);
            *(short*)(thisPtr + 0x78) = shortVal; // +0x78: first short property
            break;
        }
        case 5:
        {
            int node = streamReadNext();
            short shortVal = *(short*)(node + 8);
            *(short*)(thisPtr + 0x7a) = shortVal; // +0x7a: second short property
            break;
        }
        case 6:
        {
            int node = streamReadNext();
            short shortVal = *(short*)(node + 8);
            *(short*)(thisPtr + 0x7c) = shortVal; // +0x7c: third short property
            break;
        }
        case 7:
        {
            int node = streamReadNext();
            int rawInt = *(int*)(node + 8);
            float floatVal = (float)rawInt;
            if (rawInt < 0) {
                floatVal = floatVal + 0x4f800000; // DAT_00e44578: magic constant for negative float conversion
            }
            *(float*)(thisPtr + 0x80) = floatVal; // +0x80: first float property
            break;
        }
        case 8:
        {
            int node = streamReadNext();
            int rawInt = *(int*)(node + 8);
            float floatVal = (float)rawInt;
            if (rawInt < 0) {
                floatVal = floatVal + 0x4f800000;
            }
            *(float*)(thisPtr + 0x84) = floatVal; // +0x84: second float property
            break;
        }
        case 9:
        {
            streamReadNext();
            const char* strVal = streamReadString();
            setStringField((void*)(thisPtr + 0x60), strVal); // +0x60: third string property
            break;
        }
        case 10:
        {
            int node = streamReadNext();
            bool boolVal = *(int*)(node + 8) != 0;
            *(bool*)(thisPtr + 0x98) = boolVal; // +0x98: second bool property
            break;
        }
        default:
            break;
        }

        // End processing for current token
        streamEndTokenRead();
        hasMore = streamHasMoreData();
    }
}