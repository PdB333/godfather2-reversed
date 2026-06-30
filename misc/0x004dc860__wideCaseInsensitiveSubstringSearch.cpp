// FUNC_NAME: wideCaseInsensitiveSubstringSearch
void __fastcall wideCaseInsensitiveSubstringSearch(const ushort* pattern, const ushort* str)
{
    // Case-insensitive wide character substring search.
    // Returns when pattern is found (pattern end reached) or when str is exhausted.
    if (*str == 0) {
        return;
    }

    int offset = (int)str - (int)pattern; // byte offset between str and pattern pointers
    ushort currentPatternChar = *pattern;
    const ushort* patternCursor = pattern;

    do {
        if (currentPatternChar != 0) {
            uint strChar = (uint)*(ushort*)(offset + (int)patternCursor); // character from str at same offset as patternCursor
            uint patChar = (uint)currentPatternChar;

            // Convert uppercase letters (0x41-0x5A) to lowercase (0x61-0x7A)
            if (strChar - 0x41 < 0x1a) {
                strChar += 0x20;
            }
            if (patChar - 0x41 < 0x1a) {
                patChar += 0x20;
            }

            if (strChar == patChar) {
                // Characters match; check if pattern end reached
                if (patternCursor[1] == 0) {
                    return; // Pattern found
                }
                // Advance pattern cursor and continue matching
                currentPatternChar = patternCursor[1];
                patternCursor = patternCursor + 1;
                continue;
            }
        }
        // Mismatch or pattern empty; move to next position in str
        str = str + 1;
        offset = offset + 2; // advance by 2 bytes (one ushort)
        currentPatternChar = *pattern;
        patternCursor = pattern;
    } while (*str != 0);
}