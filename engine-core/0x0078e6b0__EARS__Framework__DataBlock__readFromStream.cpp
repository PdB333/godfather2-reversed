// FUNC_NAME: EARS::Framework::DataBlock::readFromStream
void __thiscall DataBlock::readFromStream(int this, Stream* stream) {
    char hasMore;
    int subType;
    uint32_t* blockPtr;

    stream->open(stream);
    stream->writeTag(stream, 0xb390b11a);
    stream->writeByte(stream, 1);
    blockPtr = stream->beginRead(stream);
    stream->readArray(stream);
    // Copy the 32-word array from stream's temporary buffer
    uint32_t tempArray[32];
    tempArray[0x1c] = 0; // fill gaps added by decompiler
    tempArray[0x10] = 0;
    tempArray[0x4] = 0;
    tempArray[0x30] = _DAT_00d5780c; // global constant
    tempArray[31] = _DAT_00d5780c;
    // ... (other elements from the actual stream read)
    memcpy(this + 0x50, &tempArray, 0x80);
    stream->writeTag(stream, 0x73354dbf);
    hasMore = stream->isEnd(stream);
    while (hasMore == 0) {
        stream->beginRead(stream);
        subType = stream->readType(stream);
        if (subType == 0) {
            stream->beginRead(this + 0x90);
            stream->readBlock(this + 0x90);
        } else if (subType == 1) {
            stream->beginRead(stream);
            *(uint32_t*)(this + 0xa0) = *(uint32_t*)(stream->getBuffer() + 8);
        }
        stream->next(stream);
        hasMore = stream->isEnd(stream);
    }
}