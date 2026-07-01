// FUNC_NAME: parseBinaryChunk
void __thiscall parseBinaryChunk(void* this, void* stream)
{
    char isEnd;
    int type;
    void* node;

    beginStream(stream);                               // Initialize stream reading
    setHash(stream, 0xceb9b7e7);                       // Set expected chunk hash/magic

    isEnd = isEndOfStream(stream);
    while (isEnd == '\0') {
        node = getNextNode(stream);                    // Get next data node
        type = getNodeType(stream);                    // Get node type identifier
        switch (type) {
            case 0:
                *(undefined4 *)((int)this + 0x5c) = *(undefined4 *)((int)node + 8); // +0x5c field
                break;
            case 4:
                *(undefined4 *)((int)this + 0x50) = *(undefined4 *)((int)node + 8); // +0x50 field
                break;
            case 5:
                *(undefined4 *)((int)this + 0x54) = *(undefined4 *)((int)node + 8); // +0x54 field
                break;
            case 6:
                *(undefined4 *)((int)this + 0x58) = *(undefined4 *)((int)node + 8); // +0x58 field
                break;
        }
        advanceStream(stream);                         // Move to next element
        isEnd = isEndOfStream(stream);
    }
    return;
}