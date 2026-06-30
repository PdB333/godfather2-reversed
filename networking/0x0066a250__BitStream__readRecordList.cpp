// FUNC_NAME: BitStream::readRecordList
int readRecordList(BitStream* stream, int* recordHeader, int compressionMode)
{
    void* tempBuffer;
    uint bitIndex;
    int status;
    int totalBitCount;
    int currentBitOffset;
    int headerSize;
    int unknownFlag;
    void* allocatedBuffer;

    tempBuffer = _calloc(4, 0x40);
    if (tempBuffer == (void*)0x0) {
        return -2;
    }

    status = *recordHeader;
    currentBitOffset = 0;
    headerSize = 0x40;
    unknownFlag = 0;

    if (status == 0) {
        totalBitCount = 0;
    }
    else {
        totalBitCount = status * 0x1c + -0x1c;
        for (bitIndex = *(uint*)(recordHeader[3] + -4 + status * 4); bitIndex != 0; bitIndex = bitIndex >> 1) {
            totalBitCount = totalBitCount + 1;
        }
    }

    status = readRecordHeader(stream, totalBitCount, &currentBitOffset, stream);
    while (((status == 0 &&
             ((compressionMode == 1 || (status = checkCompressionMode(&currentBitOffset, compressionMode, &currentBitOffset), status == 0)) &&
              (status = readRecordPayload(stream, &currentBitOffset), status == 0)))) &&
           (status = checkEndOfRecords(), status != -1))) {
        processNextRecord(stream);
        status = readRecordHeader(stream, totalBitCount, &currentBitOffset, stream);
    }

    allocatedBuffer = tempBuffer;
    if (tempBuffer != (void*)0x0) {
        _memset(tempBuffer, 0, currentBitOffset * 4);
        _free(allocatedBuffer);
    }
    return status;
}