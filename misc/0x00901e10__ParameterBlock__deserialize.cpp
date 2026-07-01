// FUNC_NAME: ParameterBlock::deserialize
void __thiscall ParameterBlock::deserialize(ParameterBlock *this, void *stream) {
    char hasMore;
    unsigned int tokenType;
    int tokenPtr;

    serializerInit(stream);
    serializerReadSignature(stream, 0x739d2757);
    hasMore = serializerHasMoreTokens();
    while (hasMore == 0) {
        serializerNextToken();
        tokenType = serializerGetTokenType();
        switch (tokenType) {
        case 0:
            serializerNextToken();
            tokenType = serializerGetTokenValue();
            serializerSetFloatAtOffset(this + 0x50, tokenType);
            break;
        case 1:
            serializerNextToken();
            tokenType = serializerGetTokenValue();
            serializerSetIntAtOffset(this + 0x58, tokenType);
            break;
        case 2:
            tokenPtr = serializerNextToken();
            *(float *)(this + 0x60) = *(float *)(tokenPtr + 8) * someScaleFactor;
            break;
        case 3:
            tokenPtr = serializerNextToken();
            *(int *)(this + 0x64) = *(int *)(tokenPtr + 8);
            break;
        case 4:
            tokenPtr = serializerNextToken();
            *(int *)(this + 0x68) = *(int *)(tokenPtr + 8);
            break;
        case 5:
            tokenPtr = serializerNextToken();
            *(int *)(this + 0x6c) = *(int *)(tokenPtr + 8);
            break;
        }
        serializerEndToken();
        hasMore = serializerHasMoreTokens();
    }
    return;
}