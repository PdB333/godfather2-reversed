// FUNC_NAME: FileListBuilder::buildString
// Reconstructed from 0x0068fc60
bool __thiscall FileListBuilder::buildString(char *outputBuffer, size_t bufferSize)
{
    rsize_t copyLen;
    bool hasMore;
    int outputIndex;
    char tempBuf[2048];
    char hasPrefix;
    char *nextStrPtr;
    rsize_t nextStrLen;
    int unused;
    int dataBase;          // +0x?? base pointer to string array
    int dataOffset;        // +0x?? current index/offset
    rsize_t dataLen;       // +0x?? length of current string chunk
    char chunk[16];        // buffer for readNext operation

    // Global flag: if not initialized, return false
    if (g_initializedFlag == 0) {
        return false;
    }

    // Initialize enumerator state (setup internal data pointers)
    this->init();

    outputIndex = 0;
    *outputBuffer = '\0';
    memset(outputBuffer, 0, bufferSize);

    hasPrefix = 0;
    hasMore = this->hasMore();
    if (hasMore != false) {
        hasPrefix = 1;
        do {
            // Copy a pre-existing chunk from internal data (e.g., prefix or fixed string)
            copyLen = dataLen;
            _strncpy_s(outputBuffer + outputIndex, bufferSize - outputIndex,
                       (char *)(dataBase + dataOffset), dataLen);
            nextStrPtr = tempBuf;
            outputIndex += copyLen;
            nextStrLen = 0;
            unused = 0x800;
            tempBuf[0] = '\0';

            // Read next item from the enumeration into tempBuf
            hasMore = this->readNext(chunk, 0, &nextStrPtr);
            copyLen = nextStrLen;
            if (hasMore != false) {
                // Append the newly read string to output
                _strncpy_s(outputBuffer + outputIndex, bufferSize - outputIndex,
                           nextStrPtr, nextStrLen);
                outputIndex += copyLen;
            }
            else {
                // Cleanup on failure (chunk may hold temporary state)
                this->cleanup(chunk);
            }
            hasMore = this->hasMore();
        } while (hasMore != false);
        // Final copy of the same base chunk (maybe a terminator or suffix)
        _strncpy_s(outputBuffer + outputIndex, bufferSize - outputIndex,
                   (char *)(dataBase + dataOffset), dataLen);
    }
    return hasPrefix != 0;
}