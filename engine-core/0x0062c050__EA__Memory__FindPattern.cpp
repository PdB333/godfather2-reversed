// FUNC_NAME: EA::Memory::FindPattern
// Address: 0x0062c050
// Implements binary pattern search (memmem) with optimized byte-by-byte and 4-byte aligned comparison.
// Returns pointer to first occurrence of pattern in buffer, or NULL if not found.
byte* FindPattern(const byte* buffer, size_t bufferSize, const char* pattern, size_t patternSize)
{
    if (patternSize == 0)
    {
        return const_cast<byte*>(buffer);
    }

    if (bufferSize < patternSize)
    {
        return nullptr;
    }

    size_t maxSearchLen = bufferSize - patternSize + 1; // maximum number of starting positions to check
    size_t remaining = maxSearchLen;
    const byte* searchPtr = buffer;

    while (true)
    {
        // Search for first byte of pattern
        const byte* firstMatch = (const byte*)memchr(searchPtr, pattern[0], remaining);
        if (firstMatch == nullptr)
        {
            return nullptr;
        }

        // Compare rest of pattern, optimized with 4-byte chunks
        const byte* p = firstMatch + 1;
        const char* pat = pattern + 1;
        size_t len = patternSize - 1;

        // Aligned 4-byte comparison
        while (len >= 4)
        {
            if (*(const int*)p != *(const int*)pat)
            {
                goto mismatch;
            }
            p += 4;
            pat += 4;
            len -= 4;
        }

        // Remaining bytes (0-3)
        if (len > 0)
        {
            if (*p != *pat) goto mismatch;
            if (len > 1)
            {
                if (p[1] != pat[1]) goto mismatch;
                if (len > 2)
                {
                    if (p[2] != pat[2]) goto mismatch;
                    if (len > 3 && p[3] != pat[3]) goto mismatch;
                }
            }
        }

        // Match found
        return const_cast<byte*>(firstMatch);

mismatch:
        // Advance search position
        size_t advance = (firstMatch - searchPtr) + 1;
        if (advance > remaining)
        {
            return nullptr;
        }
        remaining -= advance;
        searchPtr = firstMatch + 1;
    }
}