// FUNC_NAME: eaEARSString_setupFromCString
void __fastcall eaEARSString_setupFromCString(const char* source, int* destBuffer)
{
    // Find null terminator to get string length
    const char* ptr = source;
    while (*ptr != '\0') {
        ++ptr;
    }
    int length = ptr - source; // number of characters before null

    // Compute aligned buffer size: ( (length + 1) * 2 + 0x15 ) & ~3
    // The +1 for null terminator, *2 unknown (maybe for potential wide char or padding),
    // +0x15 unknown, then align down to 4 bytes.
    int rawSize = (length + 1) * 2 + 0x15;
    int alignedSize = rawSize - (rawSize & 3);  // align to 4

    if (destBuffer != nullptr)
    {
        // Header: offset 0 = allocated size, offset 4 = flags (0x20000000 = allocated)
        destBuffer[0] = alignedSize;          // +0x00
        destBuffer[1] = 0x20000000;           // +0x04

        // Copy the source string (including null terminator) to offset 8
        char* dest = reinterpret_cast<char*>(destBuffer) + 8; // +0x08
        const char* src = source;
        do {
            *dest++ = *src;
        } while (*src++ != '\0');
    }
}