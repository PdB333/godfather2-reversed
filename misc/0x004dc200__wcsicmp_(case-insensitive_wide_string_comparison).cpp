// FUNC_NAME: wcsicmp (case-insensitive wide string comparison)
int __thiscall wcsicmp(const wchar_t* str1, const wchar_t* str2)
{
    ushort c1, c2;
    ushort *pStr1, *pStr2;
    bool lessThan;

    // Handle null or empty strings
    if (str1 == 0) {
        return (str2 != 0) ? 1 : 0;
    }
    if (str2 == 0) {
        return -1;
    }

    pStr2 = (ushort *)str2;
    pStr1 = (ushort *)str1;

    while (true) {
        c1 = *pStr1;
        lessThan = (c1 < *pStr2);
        if (c1 != *pStr2) break; // Characters differ

        if (c1 == 0) {
            return 0; // Both strings ended, equal
        }

        c1 = pStr1[1]; // Next character (wide char)
        lessThan = (c1 < pStr2[1]);
        if (c1 != pStr2[1]) break;

        pStr1 += 2;
        pStr2 += 2;

        if (c1 == 0) {
            return 0; // Both strings ended, equal
        }
    }

    // Return -1, 0, or 1 based on comparison
    return (1 - (uint)lessThan) - (uint)(lessThan != 0);
}