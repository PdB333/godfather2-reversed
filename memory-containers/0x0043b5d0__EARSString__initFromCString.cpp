// FUNC_NAME: EARSString::initFromCString
void __fastcall EARSString::initFromCString(char *srcString, int *destBuffer)
{
    uint alignedSize;
    char c;
    int offset;
    char *pSrc;

    // Calculate length of source string
    pSrc = srcString;
    do {
        c = *pSrc;
        pSrc = pSrc + 1;
    } while (c != '\0');

    // Compute total buffer size: length * 2 + 0x15, aligned to 4 bytes
    alignedSize = ((int)pSrc - (int)(srcString + 1)) * 2 + 0x15;
    if (destBuffer != (int *)0x0) {
        *destBuffer = alignedSize - (alignedSize & 3);  // +0x00: allocated size (multiple of 4)
        destBuffer[1] = -0x80000000;                    // +0x04: flags (0x80000000 = "unmanaged" or "empty")
        offset = 8 - (int)srcString;
        // Copy string to buffer starting at offset +8 (destBuffer[2..])
        do {
            c = *srcString;
            srcString[(int)destBuffer + offset] = c;   // Equivalent to: ((char*)destBuffer)[8 + copyIndex]
            srcString = srcString + 1;
        } while (c != '\0');
    }
    return;
}