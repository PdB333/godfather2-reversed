// FUNC_NAME: wcsFirstNotInSet
// Address: 0x006a3840
// Returns the index of the first character in 'string' that is not present in 'allowedChars'.
// Returns -1 if all characters in 'string' are found in 'allowedChars' or if 'string' is empty.
// Both strings are null-terminated wide character arrays (uint16_t).
int wcsFirstNotInSet(const uint16_t* string, const uint16_t* allowedChars)
{
    int index = 0;

    // Only proceed if the string is non-empty
    if (*string != 0)
    {
        do
        {
            int charsetIndex = 0;

            // If allowed set is empty, the first character is automatically not allowed
            if (*allowedChars == 0)
            {
                return index;
            }

            uint16_t currentChar = *allowedChars;

            // Search for string[index] within allowedChars
            while (string[index] != currentChar)
            {
                // Move to next allowed character
                currentChar = allowedChars[charsetIndex + 1];
                charsetIndex++;

                // If end of allowed set reached, this character is not allowed
                if (currentChar == 0)
                {
                    return index;
                }
            }

            // Character is in allowed set, move to next position
            index++;
        } while (string[index] != 0);
    }

    // All characters are allowed or string is empty
    return -1;
}