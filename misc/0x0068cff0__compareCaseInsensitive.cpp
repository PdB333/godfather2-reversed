// FUNC_NAME: compareCaseInsensitive
// Address: 0x0068cff0
// Role: Case-insensitive string comparison with null-pointer handling.
// Compares two strings using stricmp if both are non-null; otherwise compares addresses (nulls are considered lower).
int __fastcall compareCaseInsensitive(const char* strA, const char* strB)
{
    // If both are non-null, perform standard case-insensitive comparison.
    if (strA != nullptr && strB != nullptr)
    {
        return __stricmp(strA, strB);
    }

    // Null-handling: treat null as "less" than any non-null pointer.
    if (strB < strA)        // strB is null, strA is non-null? Actually, if strA is null, strB < strA would be false since null is less.
    {
        return -1;          // strB is "less" than strA
    }
    else
    {
        // Return 1 if strA is less than strB, 0 if equal (both null).
        return (uint)(strA < strB);
    }
}