// FUNC_NAME: BufferWriter::appendBracketByteArray

struct ByteArrayRef {
    char* m_pData;      // +0x00: pointer to data buffer
    int   field_0x04;   // +0x04: unknown (unused here)
    int   m_nOffset;    // +0x08: offset within m_pData
    int   m_nLength;    // +0x0C: length of the sub-array
};

struct BufferWriter {
    char* m_pBase;      // +0x00: start of writable buffer
    char* m_pCurrent;   // +0x04: current write position
    char* m_pEnd;       // +0x08: end of buffer (one past last writable byte)
};

void __thiscall BufferWriter::appendBracketByteArray(int *thisPtr, int *sourcePtr) {
    // Reinterpret pointers as the actual structures
    BufferWriter *writer = (BufferWriter *)thisPtr;
    ByteArrayRef *source = (ByteArrayRef *)sourcePtr;

    rsize_t remaining = writer->m_pEnd - writer->m_pCurrent;

    // Write opening tag "[b="
    _strncpy_s(writer->m_pCurrent, remaining, "[b=", 3);
    writer->m_pCurrent += 3;

    // Write the byte array content (length is source->m_nLength)
    remaining = writer->m_pEnd - writer->m_pCurrent;
    char *src = source->m_pData + source->m_nOffset;
    _strncpy_s(writer->m_pCurrent, remaining, src, source->m_nLength);
    writer->m_pCurrent += source->m_nLength;

    // Write closing bracket "]"
    remaining = writer->m_pEnd - writer->m_pCurrent;
    _strncpy_s(writer->m_pCurrent, remaining, "]", 1);
    writer->m_pCurrent += 1;
}