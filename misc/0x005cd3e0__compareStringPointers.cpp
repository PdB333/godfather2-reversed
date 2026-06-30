// FUNC_NAME: compareStringPointers
bool __fastcall compareStringPointers(wchar_t** thisPtr, wchar_t** otherPtr)
{
    wchar_t* str1 = *thisPtr;
    wchar_t* str2 = *otherPtr;

    // If both pointers are the same, strings are equal
    if (thisPtr == otherPtr)
        return true;

    // Null check: if either string pointer is null, they are not equal
    if (str1 == nullptr || str2 == nullptr)
        return false;

    // Compare two wide characters at a time (16-bit chars)
    while (true)
    {
        wchar_t c1 = *str1;
        wchar_t c2 = *str2;

        if (c1 != c2)
            return false;    // Characters differ, not equal
        if (c1 == L'\0')
            return true;     // End of string reached, equal

        // Advance and compare next character
        str1++;
        str2++;
    }
}