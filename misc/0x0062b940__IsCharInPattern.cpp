// FUNC_NAME: IsCharInPattern
// Function address: 0x0062b940
// Role: Pattern matching for character sets. Supports negation ('^' prefix), ranges ('a-z'), and escape sequences ('%').
// The pattern is a contiguous bytes buffer defined by patternStart (passed in EAX in assembly) and patternEnd (param_2).
// The function returns true if the input character ch matches the pattern, false otherwise.

bool IsCharInPattern(const char* patternStart, unsigned int ch, const char* patternEnd)
{
    bool negated = (patternStart[1] == '^');  // Check if pattern starts with '^' (negation indicator)
    if (negated)
    {
        patternStart++;  // Skip the '^' so the actual pattern begins at patternStart+1
    }

    bool result = !negated;  // Default return value: true if not negated, false if negated

    const char* pCurrent = patternStart + 1;  // Pointer walking through the pattern (start after the first char? but patternStart might have been incremented if negated)
    const char* pNext = patternStart + 3;     // pNext is always 2 bytes ahead of pCurrent (used for range detection)

    if (pCurrent < patternEnd)
    {
        do
        {
            if (*pCurrent == '%')
            {
                // Percent escape: skip the '%' and check the next character via helper function
                pCurrent++;
                pNext++;
                if (FUN_0062b830())  // This function probably validates the escaped character
                {
                    return result;  // Return current default value
                }
            }
            else if ((pCurrent[1] == '-') && (pNext < patternEnd))
            {
                // Range pattern: "x-y" where x is the start, y is the end
                char rangeStart = *pCurrent;
                pCurrent += 2;  // Skip past the hyphen to the range end
                pNext += 2;
                if ((rangeStart <= ch) && (ch <= *pCurrent))
                {
                    return result;  // Match found
                }
            }
            else if (*pCurrent == ch)
            {
                return result;  // Exact character match
            }

            pCurrent++;
            pNext++;
        } while (pCurrent < patternEnd);
    }

    return !result;  // No match: return opposite of default
}