// FUNC_NAME: StringBuffer::append
void __thiscall StringBuffer::append(int* thisPtr, const char* sourceString) {
    // Struct layout:
    // +0x00: char* bufferBase
    // +0x04: int writeOffset
    // +0x08: int bufferSize (capacity)
    char* bufferBase = reinterpret_cast<char*>(thisPtr[0]);
    int& writeOffset = thisPtr[1];
    int bufferSize = thisPtr[2];

    // Compute length of sourceString (including null terminator scan)
    const char* scanPtr = sourceString;
    char c;
    do {
        c = *scanPtr;
        scanPtr++;
    } while (c != '\0');
    int srcLen = (scanPtr - (sourceString + 1)); // strlen(sourceString)

    // Safe copy into buffer at current write position
    strncpy_s(bufferBase + writeOffset, bufferSize - writeOffset, sourceString, srcLen);

    // Advance write offset
    writeOffset += srcLen;
}