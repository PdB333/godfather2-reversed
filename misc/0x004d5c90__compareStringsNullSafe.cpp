// FUNC_NAME: compareStringsNullSafe
uint __fastcall compareStringsNullSafe(char *str1, char *str2)
{
    // If both pointers are valid, perform case-insensitive string comparison.
    if ((str1 != nullptr) && (str2 != nullptr)) {
        return __stricmp(str1, str2);
    }
    // Handle null pointers: compare the pointer values themselves.
    // Return -1 if str2 is less than str1, 1 if str1 is less than str2, 0 if equal.
    if (str2 < str1) {
        return 0xFFFFFFFF; // -1
    }
    return (uint)(str1 < str2); // 1 if str1 < str2, else 0
}