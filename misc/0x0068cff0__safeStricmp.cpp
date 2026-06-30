// FUNC_NAME: safeStricmp
int __fastcall safeStricmp(const char* strA, const char* strB)
{
    // If both strings are valid, use case-insensitive comparison
    if (strA != nullptr && strB != nullptr)
    {
        return __stricmp(strA, strB);
    }

    // Fallback: compare pointer values to establish ordering when one or both are null
    // Null pointers are treated as less than any valid pointer.
    if (strB < strA)
        return -1;
    else if (strA < strB)
        return 1;
    else
        return 0;
}