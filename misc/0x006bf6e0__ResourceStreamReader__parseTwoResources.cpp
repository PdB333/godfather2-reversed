// FUNC_NAME: ResourceStreamReader::parseTwoResources
void __thiscall ResourceStreamReader::parseTwoResources(void* this, void* streamBuffer) {
    char isEnd;
    int chunkType;
    void* chunkData;

    initStreamReader(streamBuffer);
    checkStreamMagic(streamBuffer, 0x106b846e);
    isEnd = isStreamEnd();
    while (isEnd == '\0') {
        readChunk();
        chunkType = getChunkType();
        if (chunkType == 0) {
            chunkData = readChunk();
            *(int*)((int)this + 0x180) = *(int*)((int)chunkData + 8);
        } else if (chunkType == 1) {
            chunkData = readChunk();
            *(int*)((int)this + 0x184) = *(int*)((int)chunkData + 8);
        }
        advanceStream();
        isEnd = isStreamEnd();
    }
}