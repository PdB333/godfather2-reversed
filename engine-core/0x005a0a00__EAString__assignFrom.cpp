// FUNC_NAME: EAString::assignFrom
// Address: 0x005a0a00
// Role: Copy constructor/assign for a custom string class with small string optimization (SSO)
// Note: This method copies data from a source string into this string.
// Structure offsets: +0x00 capacity, +0x04 size, +0x08 buffer pointer, +0x0C inline char buffer (16 bytes)

void __thiscall EAString::assignFrom(int *this, int *srcString)
{
    int srcLen;
    int *inlinePtr;
    int *allocatedBuffer;
    char *srcBuf;
    char *dstBuf;
    char *srcEnd;

    // Initialize: start with inline buffer
    srcLen = *srcString;                                    // +0x00 of source: length (or capacity)
    *this = srcLen;                                         // set capacity
    this[1] = srcLen;                                       // set size
    inlinePtr = this + 3;                                    // +0x0C (inline buffer start)
    this[2] = (int)inlinePtr;                               // buffer points to inline storage
    inlinePtr[0] = 0;                                       // zero first 8 bytes of inline
    inlinePtr[1] = 0;
    this[5] = 0;                                            // zero next 8 bytes
    this[6] = 0;

    // Check if we need to allocate heap buffer (if source length >= 16)
    srcLen = *this;                                         // re-read capacity (now equals source length)
    if (srcLen >= 0x10) {
        this[1] = *srcString;                               // ensure size is correct (redundant)
        if (srcLen + 1 == 0) {
            this[2] = 0;                                    // allocation failed (should not happen)
        } else {
            allocatedBuffer = (int *)(*DAT_0119caf0)(srcLen + 1, 0);  // allocate memory (malloc or EA allocator)
            this[2] = (int)allocatedBuffer;
        }
    }

    // Copy the string data (including null terminator)
    srcBuf = (char *)srcString[2];                          // +0x08 of source
    dstBuf = (char *)this[2];                               // target buffer
    srcEnd = srcBuf + *this;                                // +0x00 of this (size)
    while (srcBuf != srcEnd) {
        *dstBuf = *srcBuf;
        srcBuf++;
        dstBuf++;
    }
    *(char *)(this[2] + *this) = '\0';                      // null terminate
}