// FUNC_NAME: stristr
char* __thiscall stristr(char* pattern, char* str)
{
    // This function performs a case-insensitive substring search.
    // Returns a pointer to the first occurrence of 'pattern' in 'str',
    // or nullptr if not found.
    // Uses ASCII-to-lowercase conversion by adding 0x20 to uppercase letters (A-Z, 0x41-0x5A).
    if (*str == '\0') {
        return nullptr;
    }

    char patternChar;
    char* patternPtr;
    int offset = (int)str - (int)pattern; // offset to translate pattern addresses to str addresses

    // Outer loop over each starting position in str
    while (*str != '\0') {
        patternChar = *pattern;
        patternPtr = pattern;

        // Inner loop: compare characters case-insensitively
        while (patternChar != '\0') {
            // Get corresponding character from str using offset
            int strChar = (int)*(patternPtr + offset); // effectively *(str + (patternPtr - pattern))
            int patChar = (int)patternChar;

            // Convert to lowercase if uppercase
            if ((strChar - 'A') < 26) {
                strChar += 0x20;
            }
            if ((patChar - 'A') < 26) {
                patChar += 0x20;
            }

            if (strChar != patChar) {
                break; // mismatch, move to next start position
            }

            // Check if pattern ends here
            if (*(patternPtr + 1) == '\0') {
                return str; // successfully matched entire pattern
            }

            // Move to next character in both strings
            patternChar = *(patternPtr + 1);
            patternPtr = patternPtr + 1;
            // offset remains unchanged because patternPtr advances
            // and the str character is always at (patternPtr + offset)
        }

        // Advance str to next start position
        str++;
        offset++; // adjust offset so patternPtr maps to str correctly
    }

    return nullptr; // pattern not found
}