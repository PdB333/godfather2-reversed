// FUNC_NAME: ConfigData::readFromStream
// Function address: 0x0090a1d0
// Role: Deserializes configuration data from a stream, reading tagged fields and clamping a value.

void __thiscall ConfigData::readFromStream(int thisPtr, undefined4 streamPtr)
{
    char hasMore;
    undefined4 tag;
    undefined4 *vecPtr;
    int intPtr;
    
    // Initialize stream and set magic identifier
    StreamReader::init(streamPtr);
    StreamReader::setMagic(streamPtr, 0x57737500); // "Wsu\0" magic
    
    hasMore = StreamReader::hasMore(streamPtr);
    while (hasMore == '\0') {
        StreamReader::advance(streamPtr);
        tag = StreamReader::readTag(streamPtr);
        switch(tag) {
        case 0:
            // Read integer and set field at +0x50
            StreamReader::advance(streamPtr);
            tag = StreamReader::readInt(streamPtr);
            setField0x50(thisPtr + 0x50, tag);
            break;
        case 1:
            // Read vector4 and store at +0x58 to +0x64
            StreamReader::advance(streamPtr);
            vecPtr = (undefined4 *)StreamReader::readVector4(streamPtr);
            *(undefined4 *)(thisPtr + 0x58) = *vecPtr;
            *(undefined4 *)(thisPtr + 0x5c) = vecPtr[1];
            *(undefined4 *)(thisPtr + 0x60) = vecPtr[2];
            *(undefined4 *)(thisPtr + 0x64) = vecPtr[3];
            break;
        case 2:
            // Read integer and set field at +0x68
            intPtr = StreamReader::advance(streamPtr);
            *(undefined4 *)(thisPtr + 0x68) = *(undefined4 *)(intPtr + 8);
            break;
        case 3:
            // Read integer, mask with 0xfc, and set field at +0x6c
            intPtr = StreamReader::advance(streamPtr);
            *(uint *)(thisPtr + 0x6c) = *(uint *)(intPtr + 8) & 0xfc;
            break;
        case 4:
            // Read integer and OR into field at +0x70
            intPtr = StreamReader::advance(streamPtr);
            *(uint *)(thisPtr + 0x70) = *(uint *)(thisPtr + 0x70) | *(uint *)(intPtr + 8);
        }
        StreamReader::endRead(streamPtr);
        hasMore = StreamReader::hasMore(streamPtr);
    }
    
    // Clamp field at +0x68 to range [3, 5]
    if (*(uint *)(thisPtr + 0x68) < 3) {
        *(undefined4 *)(thisPtr + 0x68) = 3;
        return;
    }
    if (5 < *(uint *)(thisPtr + 0x68)) {
        *(undefined4 *)(thisPtr + 0x68) = 5;
    }
    return;
}