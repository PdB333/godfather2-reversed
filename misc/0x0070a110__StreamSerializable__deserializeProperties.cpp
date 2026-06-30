// FUNC_NAME: StreamSerializable::deserializeProperties
void __thiscall StreamSerializable::deserializeProperties(int thisPtr, void* stream)
{
    char isDone;
    uint chunkType;
    int chunkPtr;

    streamBegin(stream);
    streamSetFormat(stream, 0x7c41a929);
    isDone = isStreamEnd(stream);
    while (isDone == '\0') {
        readNextChunk(stream);
        chunkType = getChunkType(stream);
        switch(chunkType) {
        case 0:
            readNextChunk(stream);
            setFloatProperty(thisPtr + 0x5c, getChunkFloatValue(stream));
            break;
        case 1:
            readNextChunk(stream);
            setFloatProperty(thisPtr + 0x64, getChunkFloatValue(stream));
            break;
        case 2:
            readNextChunk(stream);
            setIntProperty(thisPtr + 0x6c, getChunkIntValue(stream));
            break;
        case 3:
            readNextChunk(stream);
            setIntProperty(thisPtr + 0x74, getChunkIntValue(stream));
            break;
        case 4:
            chunkPtr = readNextChunk(stream);
            *(int*)(thisPtr + 0x54) = *(int*)(chunkPtr + 8);
            break;
        case 5:
            chunkPtr = readNextChunk(stream);
            *(int*)(thisPtr + 0x50) = *(int*)(chunkPtr + 8);
            break;
        case 6:
            chunkPtr = readNextChunk(stream);
            *(int*)(thisPtr + 0x58) = *(int*)(chunkPtr + 8);
            break;
        }
        finishChunk(stream);
        isDone = isStreamEnd(stream);
    }
    return;
}