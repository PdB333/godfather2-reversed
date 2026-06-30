// FUNC_NAME: writeStringToBuffer
int writeStringToBuffer(const char* source, bool clearBeforeWrite, int* bufferInfo)
{
    // bufferInfo[0] = pointer to buffer data
    // bufferInfo[1] = current write position (offset)
    // bufferInfo[2] = total buffer capacity

    if (source == nullptr)
        return 0;

    if (clearBeforeWrite)
    {
        memset((void*)bufferInfo[0], 0, bufferInfo[2]);
    }

    // Calculate source string length
    const char* p = source;
    while (*p != '\0')
        p++;
    size_t srcLen = p - source;

    // Safe copy into buffer at current position, with remaining capacity
    char* dest = (char*)(bufferInfo[0] + bufferInfo[1]);
    size_t remaining = bufferInfo[2] - bufferInfo[1];
    _strncpy_s(dest, remaining, source, srcLen);

    // Advance write position by the copied length
    bufferInfo[1] += (int)srcLen;

    return 1;
}