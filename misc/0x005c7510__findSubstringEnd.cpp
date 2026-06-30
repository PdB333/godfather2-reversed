// FUNC_NAME: findSubstringEnd
// Address: 0x005c7510
// Role: Finds a substring (needle) in a string (haystack) and returns a pointer to the character immediately after the match, or NULL if not found.
// This is a utility function used for string parsing (e.g., skipping past a known token).

char* __fastcall findSubstringEnd(char* haystack, char* needle)
{
    char c;
    char* pNeedleEnd;
    char* result;

    // Compute length of needle by scanning to null terminator
    pNeedleEnd = needle;
    do {
        c = *pNeedleEnd;
        pNeedleEnd = pNeedleEnd + 1;
    } while (c != '\0');

    // Find first occurrence of needle in haystack
    result = _strstr(haystack, needle);
    if (result == (char*)0x0) {
        return (char*)0x0;
    }

    // Return pointer to character after the found substring
    // pNeedleEnd points one past the null terminator, so offset = strlen(needle)
    return result + (pNeedleEnd - (needle + 1));
}