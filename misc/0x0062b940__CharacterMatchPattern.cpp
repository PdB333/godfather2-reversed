// FUNC_NAME: CharacterMatchPattern
bool CharacterMatchPattern(const char* patternStart, const char* patternEnd, unsigned int ch)
{
    // patternStart points to the start of the pattern (maybe with a leading byte?)
    // patternEnd points to one past the end of the pattern
    // Check if the first character after patternStart is '^' (negation flag)
    bool negate = (patternStart[1] == '^');
    if (negate) {
        patternStart++; // skip over the '^'
    }
    negate = !negate; // now true if no '^', false if '^'

    // Pointers for pattern traversal
    const char* pPattern = patternStart + 1;   // skip potential '^' or first char
    const char* pFormat  = patternStart + 3;   // used for range detection (advances together with pPattern)

    // If the pattern is empty (no characters after prefix), return false/true based on negation
    if (pPattern >= patternEnd) {
        return !negate;
    }

    do {
        if (*pPattern == '%') {
            // Wildcard / special character? Skip this % and the next character?
            pPattern++;
            pFormat++;
            int result = FUN_0062b830(); // some helper (likely returns 0 if no match, non-zero if match)
            if (result != 0) {
                return negate; // match returns negation flag
            }
        }
        else if ((pPattern[1] == '-') && (pFormat < patternEnd)) {
            // Range: e.g., 'a-z'
            char low = *pPattern;
            pPattern += 2;
            pFormat += 2;
            if (((unsigned char)low <= ch) && (ch <= (unsigned char)*pPattern)) {
                return negate;
            }
        }
        else if (*pPattern == ch) {
            // Direct character match
            return negate;
        }
        pPattern++;
        pFormat++;
    } while (pPattern < patternEnd);

    // No match found
    return !negate;
}