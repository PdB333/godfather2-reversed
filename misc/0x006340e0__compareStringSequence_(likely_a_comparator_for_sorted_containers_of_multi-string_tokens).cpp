// FUNC_NAME: compareStringSequence (likely a comparator for sorted containers of multi-string tokens)
int __fastcall compareStringSequence(const void *objA, const void *objB)
{
    int lenA;            // length field of object A
    int lenB;            // length field of object B
    char *strA;          // string pointer for object A (embedded at +0x10)
    char *strB;          // string pointer for object B (embedded at +0x10)
    int comp;            // result of locale-aware string comparison
    int strLen;          // computed length of current null-terminated substring in A

    // Object layout: +0x0C = int (total remaining length? or length of concatenated strings)
    //                +0x10 = char array containing null-terminated strings (possibly multiple)
    lenA = *(int *)((char *)objA + 0x0C);
    lenB = *(int *)((char *)objB + 0x0C);
    strA = (char *)objA + 0x10;
    strB = (char *)objB + 0x10;

    // Compare the first null-terminated substring using locale rules
    comp = _strcoll(strA, strB);
    if (comp != 0)
        return comp;

    // Strings are equal so far; now compare the remaining concatenated substrings
    // and check the stored lengths for tie-breaking
    for (;;)
    {
        // Compute length of the current substring in A (up to but not including null)
        char *p = strA;
        while (*p != '\0')
            p++;
        strLen = (int)(p - (strA + 1));   // strlen(strA)

        if (strLen == lenA)
        {
            // If the substring length equals the stored length for A,
            // then A is exhausted – return 1 if lengths differ, 0 if equal.
            // (This acts as a lexicographic tie-breaker on total lengths)
            return (uint)(lenA != lenB);
        }

        if (strLen == lenB)
        {
            // If the substring length equals stored length for B (but not A),
            // then B is exhausted first – A is considered "greater"
            // return -1 as unsigned? The code returns 0xFFFFFFFF.
            return 0xFFFFFFFF;
        }

        // Advance past the current substring (including null)
        strLen++;               // include null terminator
        strA += strLen;
        strB += strLen;
        lenA -= strLen;
        lenB -= strLen;

        // Compare the next substring
        comp = _strcoll(strA, strB);
        if (comp != 0)
            return comp;
    }
}