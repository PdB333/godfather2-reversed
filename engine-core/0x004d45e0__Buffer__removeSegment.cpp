// FUNC_NAME: Buffer::removeSegment
// Buffer: Simple mutable byte buffer class with m_pData (char*) and m_size (int). Removes 'count' bytes starting at 'offset'.
// Shifts remaining data and null-terminates. If removal exceeds current size, truncates.
int* __thiscall Buffer::removeSegment(int* thisPtr, int offset, int count)
{
    if (count != 0)
    {
        char* bufferData = reinterpret_cast<char*>(thisPtr[0]); // +0x00: pointer to data
        int& bufferSize = thisPtr[1];                           // +0x04: current data size

        // If removal goes beyond or exactly to the end, just truncate
        if (static_cast<unsigned int>(bufferSize) <= static_cast<unsigned int>(offset + count))
        {
            bufferSize = offset;
            bufferData[offset] = '\0';
            return thisPtr;
        }

        // Move the remainder down (overwrite the removed segment)
        int bytesAfterRemoval = bufferSize - (offset + count);
        _memmove(bufferData + offset,                     // destination
                 bufferData + offset + count,             // source
                 bytesAfterRemoval);                      // length
        bufferSize -= count;
        bufferData[bufferSize] = '\0';
    }
    return thisPtr;
}