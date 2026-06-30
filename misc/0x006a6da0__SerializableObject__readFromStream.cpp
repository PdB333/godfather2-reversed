// FUNC_NAME: SerializableObject::readFromStream
// Address: 0x006a6da0
// Role: Deserializes a tagged data stream into member fields at offsets +0x50, +0x58, +0x60 (likely a string buffer)
// Called functions: stream start + set magic tag, then loop reading chunks of types 0,1,2.

void __thiscall SerializableObject::readFromStream(void* thisPtr, void* stream) {
    char streamEnd;
    int type;
    int value;

    // Start reading from stream and set expected magic tag
    streamStartReading(stream);
    streamSetMagic(stream, 0xadc23d35);

    // Check if stream is already at end
    streamEnd = streamIsEnd();
    do {
        if (streamEnd != '\0') {
            return;
        }

        // Read next chunk header
        streamReadToken(stream);
        type = streamReadType(); // returns 0, 1, or 2

        if (type == 0) {
            // Read integer value into field at +0x50
            streamReadToken(stream);
            value = streamReadValue();
            setField1(thisPtr, value);
        } else if (type == 1) {
            // Read integer value into field at +0x58
            streamReadToken(stream);
            value = streamReadValue();
            setField2(thisPtr, value);
        } else if (type == 2) {
            // Read string into field at +0x60
            char* stringBuffer = (char*)((int)thisPtr + 0x60);
            streamReadToken(stream, stringBuffer);
            streamReadString(stringBuffer);
        }

        // Advance to next chunk
        streamAdvance();
        streamEnd = streamIsEnd();
    } while (true);
}

// Helper functions (pseudocode for calls):
// void streamStartReading(void* stream);
// void streamSetMagic(void* stream, uint magic);
// char streamIsEnd();
// void streamReadToken(void* stream); // or (void* stream, void* buffer) for string
// int streamReadType();
// int streamReadValue();
// void streamReadString(char* buffer);
// void streamAdvance();
// void setField1(void* obj, int v); // stores at [obj+0x50]
// void setField2(void* obj, int v); // stores at [obj+0x58]