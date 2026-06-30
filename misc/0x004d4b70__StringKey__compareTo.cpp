// FUNC_NAME: StringKey::compareTo
// Reconstructed C++ for function at 0x004d4b70 – case-insensitive string comparator with validity flag
// Class likely used as key in sorted data structures (e.g., hash map, BST).
// Layout:
//   +0x00: char* mString        – pointer to null-terminated string
//   +0x04: int mFlags           – non-zero if the key holds a valid string

int __thiscall StringKey::compareTo(const char* otherString) const
{
    char* myString;
    bool otherNonEmpty;
    int result; // uint treated as int

    // Determine if the other string is non‑empty (including non‑null)
    otherNonEmpty = (otherString != nullptr) && (*otherString != '\0');

    // If this key is valid (mFlags != 0)
    if (this->mFlags != 0)
    {
        if (otherNonEmpty)
        {
            myString = this->mString;
            // If both strings are valid pointers, do a case‑insensitive comparison
            if ((myString != nullptr) && (otherString != nullptr))
            {
                // __stricmp returns 0 on equality, negative if myString < otherString, positive if greater
                result = __stricmp(myString, otherString);
                return result;
            }
            // Fallback: pointer comparison when one or both strings are null
            if (myString <= otherString)
            {
                // Returns 0 if equal pointers, 1 if myString < otherString (pointer order)
                return (int)(myString < otherString);
            }
        }
        // If other string is empty (or null), return -1 (less than any non‑empty string)
        return -1;
    }
    // If this key is invalid (mFlags == 0), return 1 if other is non‑empty, 0 if empty
    return (int)otherNonEmpty;
}