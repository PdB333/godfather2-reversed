// FUNC_NAME: DataChunkParser::readProperties
void __thiscall DataChunkParser::readProperties(DataChunkParser* this, StreamHandle stream) {
    char isDone;
    int tokenType;
    char* sourceStr;
    undefined4 valueData;

    // Initialize stream reader and begin chunk with magic identifier 0xd0be1d15
    initStreamReader(stream);
    beginChunk(stream, 0xd0be1d15);

    isDone = isChunkEnd();
    do {
        if (isDone != '\0') {
            return;
        }
        advanceToNextToken();

        tokenType = readTokenType();
        if (tokenType == 0) {
            // Token type 0: integer value copied to field at +0x50
            advanceToNextToken();
            valueData = readTokenData();
            setValueAtOffset(this + 0x50, valueData);
        }
        else if (tokenType == 1) {
            // Token type 1: integer value copied to field at +0x58
            advanceToNextToken();
            valueData = readTokenData();
            setValueAtOffset(this + 0x58, valueData);
        }
        else if (tokenType == 2) {
            // Token type 2: string value (max 24 chars) copied to field at +0x60
            advanceToNextToken();
            sourceStr = (char*)readTokenData();
            strncpy((char*)(this + 0x60), sourceStr, 0x18);
        }
        skipToNextToken();
        isDone = isChunkEnd();
    } while (true);
}