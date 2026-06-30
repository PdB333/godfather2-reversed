// FUNC_NAME: writeAlignedBufferHeader
int __fastcall writeAlignedBufferHeader(void* pBuffer, size_t dataSize, int dataType, void* pData)
{
    // pBuffer is expected to point to a buffer large enough for header + aligned data.
    // header layout (4 bytes each): [0] alignedSize, [4] type, [8] data...
    int* pHeader = (int*)pBuffer;
    // Align dataSize to 4-byte boundary: round up (dataSize + 11) & ~3
    int alignedSize = (dataSize + 0xb) - ((dataSize + 0xb) & 3);

    if (pHeader != nullptr) {
        *pHeader = alignedSize;      // +0x00: aligned size of data portion
        pHeader[1] = dataType;       // +0x04: type/flag
        if (pData != nullptr) {
            // Copy data after header (offset +0x08)
            memcpy(pHeader + 2, pData, dataSize);
        }
    }
    return alignedSize; // total aligned data size (may be larger than original dataSize)
}