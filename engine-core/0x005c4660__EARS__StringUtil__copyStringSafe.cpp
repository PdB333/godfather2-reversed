// FUNC_NAME: EARS::StringUtil::copyStringSafe
// Function at 0x005c4660: Safe string copy with truncation and NULL termination.
// Copies up to (destSize - 1) characters from src to dest, always appends a null terminator.
// If explicitLength is non-zero, it is used as the source length (and the function still copies destSize-1 bytes?).
void* copyStringSafe(void* dest, const char* src, int destSize, uint explicitLength)
{
    char c;
    const char* tempPtr;
    uint copyLength;

    // If no explicit length provided, compute the length of src via strlen
    if (explicitLength == 0) {
        tempPtr = src;
        do {
            c = *tempPtr;
            ++tempPtr;
        } while (c != '\0');
        explicitLength = (uint)(tempPtr - (src + 1)); // strlen = last pointer - (first+1)
    }

    // Maximum number of characters we can copy (reserve one byte for null)
    copyLength = destSize - 1;

    // If the source length fits within the buffer, and we are in the auto-length mode,
    // recalculate the copy length (redundant but preserves IDA decompiled logic)
    if ((explicitLength < copyLength) && (copyLength = explicitLength, explicitLength == 0)) {
        tempPtr = src;
        do {
            c = *tempPtr;
            ++tempPtr;
        } while (c != '\0');
        copyLength = (uint)(tempPtr - (src + 1));
    }

    // Perform the copy and null-terminate
    memcpy(dest, src, copyLength);
    *(char*)((int)dest + copyLength) = '\0';

    return dest;
}