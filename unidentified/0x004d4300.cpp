// FUN_NAME: EAString::append
// Reconstructed C++ for custom EA string class append method (dynamic buffer with custom allocator)
// Struct fields: +0x00 m_pData, +0x04 m_len, +0x08 m_capacity, +0x0C m_pDealloc
int * __thiscall EAString::append(int *thisString, char *str)
{
    uint capacity;
    char c;
    char *srcPtr;
    size_t strLen;
    void *newBuffer;

    // If input string is null or empty, return this unchanged
    if ((str == (char *)0x0) || (*str == '\0')) {
        return thisString;
    }

    // Calculate length of str (strlen)
    srcPtr = str;
    do {
        c = *srcPtr;
        srcPtr = srcPtr + 1;
    } while (c != '\0');
    strLen = (int)srcPtr - (int)(str + 1);

    // Check if buffer is already allocated (capacity != 0)
    if (thisString[2] != 0) {
        // New length after append
        uint newLen = thisString[1] + strLen;
        if (newLen < (uint)thisString[2]) {
            // Fits in current buffer: just copy the string after existing data
            memcpy((void *)(*thisString + thisString[1]), str, strLen);
        } else {
            // Need to reallocate: create larger buffer (newLen + 1 for null terminator)
            newBuffer = (void *)customAlloc(newLen + 1);
            // Copy existing data
            memcpy(newBuffer, (void *)*thisString, thisString[1]);
            // Append new string
            memcpy((void *)(thisString[1] + (int)newBuffer), str, strLen);
            // Free old buffer using stored deallocator
            if (*thisString != 0) {
                ((void (*)(void *))thisString[3])((void *)*thisString);
            }
            // Update capacity to exactly new length
            thisString[2] = newLen;
            // Set buffer pointer to new buffer
            *thisString = (int)newBuffer;
            // Set deallocator to standard customFree
            thisString[3] = (int)customFree;
        }
        // Update length
        thisString[1] = thisString[1] + strLen;
        // Null-terminate the string
        *(char *)(thisString[1] + *thisString) = '\0';
        return thisString;
    }

    // First allocation: allocate buffer exactly for strLen + null terminator
    srcPtr = (char *)customAlloc(strLen + 1);
    *thisString = (int)srcPtr;
    thisString[3] = (int)customFree;
    thisString[2] = strLen;
    // Copy the string character by character (including null terminator)
    do {
        c = *str;
        *srcPtr = c;
        str = str + 1;
        srcPtr = srcPtr + 1;
    } while (c != '\0');
    thisString[1] = strLen;
    return thisString;
}