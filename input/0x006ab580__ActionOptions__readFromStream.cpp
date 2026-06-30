// FUNC_NAME: ActionOptions::readFromStream
void __thiscall ActionOptions::readFromStream(int thisPtr, void* stream)
{
    float floatVal;
    bool streamEnd;
    int tokenType;
    int uintVal;
    int tokenCtx;

    // Initialize stream parsing
    DataStream::beginRead(stream);
    DataStream::setStream(stream, 0xe38005b9); // Version/hash token

    streamEnd = DataStream::isEndOfStream();
    while (streamEnd == '\0') {
        tokenCtx = DataStream::readNextToken();
        tokenType = DataStream::getTokenType(tokenCtx);
        switch(tokenType) {
        case 0: // int field at +0x50
            DataStream::readNextToken();
            uintVal = DataStream::getTokenValue();
            setIntField(thisPtr + 0x50, uintVal);
            break;
        case 1: // int field at +0x58
            DataStream::readNextToken();
            uintVal = DataStream::getTokenValue();
            setIntField(thisPtr + 0x58, uintVal);
            break;
        case 2: // Resource handle at +0x?? (FUN_004d3d90)
            DataStream::readNextToken();
            uintVal = DataStream::getTokenValue();
            setResourceHandle(uintVal); // Probably assigns a resource reference
            break;
        case 3: // bool at +0x99
            tokenCtx = DataStream::readNextToken();
            *(bool *)(thisPtr + 0x99) = *(int *)(tokenCtx + 8) != 0;
            break;
        case 4: // short at +0x78
            tokenCtx = DataStream::readNextToken();
            *(short *)(thisPtr + 0x78) = *(short *)(tokenCtx + 8);
            break;
        case 5: // short at +0x7a
            tokenCtx = DataStream::readNextToken();
            *(short *)(thisPtr + 0x7a) = *(short *)(tokenCtx + 8);
            break;
        case 6: // short at +0x7c
            tokenCtx = DataStream::readNextToken();
            *(short *)(thisPtr + 0x7c) = *(short *)(tokenCtx + 8);
            break;
        case 7: // float at +0x80
            tokenCtx = DataStream::readNextToken();
            floatVal = (float)*(int *)(tokenCtx + 8);
            // Handle negative int to float conversion (compensate for sign bit)
            if (*(int *)(tokenCtx + 8) < 0) {
                floatVal = floatVal + DAT_00e44578; // 2^32 as float
            }
            *(float *)(thisPtr + 0x80) = floatVal;
            break;
        case 8: // float at +0x84
            tokenCtx = DataStream::readNextToken();
            floatVal = (float)*(int *)(tokenCtx + 8);
            if (*(int *)(tokenCtx + 8) < 0) {
                floatVal = floatVal + DAT_00e44578;
            }
            *(float *)(thisPtr + 0x84) = floatVal;
            break;
        case 9: // string at +0x60
            DataStream::readNextToken();
            uintVal = DataStream::getTokenValue();
            setStringField(thisPtr + 0x60, uintVal); // Assigns string (maybe hash or pointer)
            break;
        case 10: // bool at +0x98
            tokenCtx = DataStream::readNextToken();
            *(bool *)(thisPtr + 0x98) = *(int *)(tokenCtx + 8) != 0;
        }
        DataStream::advance();
        streamEnd = DataStream::isEndOfStream();
    }
    return;
}