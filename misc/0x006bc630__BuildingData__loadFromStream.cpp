// FUNC_NAME: BuildingData::loadFromStream
void __thiscall BuildingData::loadFromStream(void *this, void *stream)
{
    char isFinished;
    int tokenType;

    beginStream(stream);
    readMagic(stream, 0x842eb5b);
    isFinished = isEndOfStream();
    while (isFinished == '\0') {
        skipToken();  // Consume current token
        tokenType = getTokenType();
        if (tokenType == 0) {
            skipToken();  // Read next token (value)
            *(int *)((int)this + 0x54) = *(int *)(getLastTokenAddress() + 8);
        }
        else if (tokenType == 1) {
            skipToken();
            *(int *)((int)this + 0x58) = *(int *)(getLastTokenAddress() + 8);
        }
        else if (tokenType == 2) {
            skipToken();
            *(bool *)((int)this + 0x50) = *(int *)(getLastTokenAddress() + 8) != 0;
        }
        advanceStream();
        isFinished = isEndOfStream();
    }
    return;
}