// FUNC_NAME: NameTable::compareString
// Function at 0x00605d60: Looks up a string by index and compares case-insensitively with the input string.
// Uses __thiscall with `this` in ESI (register). Struct offsets:
// +0x0c: Pointer to an array of 8-byte entries (each entry has a string pointer at offset 0)
// +0x14: Count of entries in the array

bool NameTable::compareString(const char* inputStr, uint32_t index)
{
    // Check if index is within valid range (count stored at +0x14)
    if (index < *(uint32_t*)(this + 0x14))
    {
        // Get the string pointer from the array at +0x0c, each entry is 8 bytes
        char* storedStr = *(char**)(*(int*)(this + 0x0c) + index * 8);

        // If both pointers are non-null, do a case-insensitive compare
        if ((inputStr != nullptr) && (storedStr != nullptr))
        {
            return __stricmp(inputStr, storedStr) == 0;
        }

        // If either is null, perform a pointer comparison and return false if stored < input
        if (storedStr < inputStr)
        {
            return false;
        }
        // Otherwise return false (default)
        return false;
    }
    // Index out of range
    return false;
}