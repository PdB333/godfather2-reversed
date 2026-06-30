// FUNC_NAME: PropertyParser::readProperties
void __thiscall PropertyParser::readProperties(int thisPtr, void* stream)
{
    char isEOF;
    int tokenType;
    int tokenValue;

    streamInit(stream);
    streamSeek(stream, 0x14064116);  // probably a magic number or offset
    isEOF = isEndOfStream(stream);
    while (isEOF == '\0') {
        readNextToken(stream);
        tokenType = getTokenType(stream);
        if (tokenType == 0) {
            readNextToken(stream);
            tokenValue = getTokenValue(stream);
            setProperty(thisPtr + 0x50, tokenValue);  // +0x50: some property
        }
        else if (tokenType == 1) {
            void* subObj = (void*)(thisPtr + 0x58);  // +0x58: sub-parser object
            readNextToken(subObj);
            processSubToken(subObj);
        }
        else if (tokenType == 2) {
            readNextToken(stream);
            // +0x68: store a pointer from token data
            *(void**)(thisPtr + 0x68) = *(void**)(stream + 8);
        }
        skipToken(stream);
        isEOF = isEndOfStream(stream);
    }
}