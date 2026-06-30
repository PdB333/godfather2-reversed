// FUNC_NAME: MemoryFindSubstring
// Address: 0x0062c050
// Role: Find first occurrence of a byte pattern (needle) in a memory buffer (haystack)
// Returns pointer to match or NULL.

byte* MemoryFindSubstring(byte* haystack, uint haystackLen, char* needle, uint needleLen)
{
    if (needleLen == 0)
        return nullptr;

    if (haystackLen < needleLen)
        return nullptr;

    // Adjust remaining length to the last possible start position for a match.
    int remaining = (int)haystackLen - (needleLen - 1);

    while (remaining > 0)
    {
        // Find first byte of pattern in the remaining haystack.
        byte* found = (byte*)_memchr(haystack, (int)*needle, (size_t)remaining);
        if (found == nullptr)
            return nullptr;

        // Compare the rest of the pattern starting from found+1.
        byte* pHaystack = found + 1;
        char* pPattern = needle + 1;
        uint compareLen = needleLen - 1;

        // Check 4 bytes at a time when possible.
        while (compareLen > 3)
        {
            if (*(int*)pHaystack != *(int*)pPattern)
                break; // mismatch
            pHaystack += 4;
            pPattern += 4;
            compareLen -= 4;
        }

        int cmpResult = 0;
        // Compare remaining bytes manually.
        while (compareLen > 0)
        {
            byte diff = *pHaystack - *pPattern;
            if (diff != 0)
            {
                cmpResult = (diff < 0) ? -1 : 1;
                break;
            }
            pHaystack++;
            pPattern++;
            compareLen--;
        }
        // If compareLen == 0 and no mismatch, then full match.
        if (cmpResult == 0)
            return found;

        // Update haystack and remaining length to search after the found position.
        int advance = (int)(pHaystack - found);
        remaining -= advance;
        haystack = pHaystack;
    }
    return nullptr;
}