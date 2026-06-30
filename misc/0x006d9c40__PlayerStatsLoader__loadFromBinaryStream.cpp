// FUNC_NAME: PlayerStatsLoader::loadFromBinaryStream
void __thiscall PlayerStatsLoader::loadFromBinaryStream(int thisPtr, undefined4 streamHandle)
{
    char isDone;
    undefined4 tokenType;
    int tokenPtr;
    
    beginBinaryRead(streamHandle, 0x3243a9f0);
    isDone = isBinaryReadComplete();
    while (isDone == '\0') {
        readNextToken(); // consume token header?
        tokenType = getTokenType();
        switch(tokenType) {
        case 0:
            readNextToken(); // read token for field1
            *(undefined4 *)(thisPtr + 0x60) = *(undefined4 *)(tokenPtr + 8); // offset +8: likely token data
            break;
        case 1:
            readNextToken();
            *(undefined4 *)(thisPtr + 100) = *(undefined4 *)(tokenPtr + 8); // field2 at +0x64
            break;
        case 2:
            readNextToken();
            *(undefined4 *)(thisPtr + 0x68) = *(undefined4 *)(tokenPtr + 8);
            break;
        case 3:
            readNextToken();
            *(undefined4 *)(thisPtr + 0x6c) = *(undefined4 *)(tokenPtr + 8);
        }
        advanceTokenPosition();
        isDone = isBinaryReadComplete();
    }
    endBinaryRead(streamHandle);
    return;
}