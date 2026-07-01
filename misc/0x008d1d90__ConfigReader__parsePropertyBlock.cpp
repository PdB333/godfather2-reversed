// FUNC_NAME: ConfigReader::parsePropertyBlock
void __thiscall ConfigReader::parsePropertyBlock(void* this, void* inputData) {
    char isEnd;
    int tokenValue;
    int tokenType;

    // Initialize stream reader (e.g., XML/Binary)
    streamInitialize(inputData);
    // Set stream to a specific hash/ID (0xfcdabbc)
    streamSetHash(inputData, 0xfcdabbc);

    isEnd = streamIsEnd();
    while (isEnd == 0) {
        streamReadNextToken(); // Advance to next token
        tokenType = streamGetTokenType(); // 0=string, 1-6=integer
        switch (tokenType) {
        case 0: { // String property
            streamReadNextToken();
            tokenValue = streamGetTokenString(); // Get string value
            setStringProperty((int)this + 0x50, tokenValue); // +0x50: string field
            break;
        }
        case 1:
            tokenValue = streamReadNextToken();
            *(int*)((int)this + 0x58) = *(int*)(tokenValue + 8); // +0x58: int field 1
            break;
        case 2:
            tokenValue = streamReadNextToken();
            *(int*)((int)this + 0x5c) = *(int*)(tokenValue + 8); // +0x5c: int field 2
            break;
        case 3:
            tokenValue = streamReadNextToken();
            *(int*)((int)this + 0x60) = *(int*)(tokenValue + 8); // +0x60: int field 3
            break;
        case 4:
            tokenValue = streamReadNextToken();
            *(int*)((int)this + 0x64) = *(int*)(tokenValue + 8); // +0x64: int field 4
            break;
        case 5:
            tokenValue = streamReadNextToken();
            *(int*)((int)this + 0x68) = *(int*)(tokenValue + 8); // +0x68: int field 5
            break;
        case 6:
            tokenValue = streamReadNextToken();
            *(int*)((int)this + 0x6c) = *(int*)(tokenValue + 8); // +0x6c: int field 6
            break;
        }
        streamAdvanceToken(); // Move to next element
        isEnd = streamIsEnd();
    }
}