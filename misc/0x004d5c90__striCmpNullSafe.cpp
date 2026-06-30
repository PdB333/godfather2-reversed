// FUNC_NAME: striCmpNullSafe
// Address: 0x004d5c90
// Role: Case-insensitive string compare with NULL pointer handling.
// Returns: <0 if str1 < str2, 0 if equal, >0 if str1 > str2.
// Note: Uses pointer comparison when either string is NULL, mimicking strcmp ordering.
#include <string.h>  // for __stricmp

unsigned int __fastcall striCmpNullSafe(const char* str1, const char* str2)
{
    // If both strings are non-null, do case-insensitive comparison
    if ((str1 != nullptr) && (str2 != nullptr))
    {
        return __stricmp(str1, str2);
    }

    // Fallback: use pointer ordering (treat NULL as lower than any non-null)
    if (str2 < str1)
    {
        return 0xFFFFFFFF;  // -1
    }
    else
    {
        return (str1 < str2) ? 1 : 0;
    }
}