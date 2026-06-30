// FUNC_NAME: EA::Text::utf8ByteOffsetForCharCount

// Note: This is a custom UTF-8 variant used in EA's EARS engine.
// The encoding handles standard 1-3 byte sequences (as in UTF-8)
// but also treats byte 0x85 as a 3-byte "fullwidth" character lead
// that consumes 1 byte in the string but advances the character count by 3.
// This is likely used for CJK or other wide characters in the game's text system.

int __cdecl utf8ByteOffsetForCharCount(const char* str, int charCount)
{
    // Guard: null pointer returns 0
    if (str == nullptr)
        return 0;

    // Find end of string (null terminator)
    const char* end = str;
    while (*end != '\0')
        end++;

    int count = 0;
    const char* current = str;

    if (current < end)
    {
        while (count < charCount)
        {
            unsigned char byte = (unsigned char)*current;

            // Single-byte character (0xxxxxxx)
            if (byte < 0x80)
            {
                count++;
                current++;
            }
            // Two-byte sequence (110xxxxx 10xxxxxx)
            else if ((byte & 0xE0) == 0xC0)
            {
                // Validate continuation byte
                if ((current[1] & 0xC0) != 0x80)
                    break;
                count++;
                current += 2;
            }
            // Three-byte sequence (1110xxxx 10xxxxxx 10xxxxxx)
            else if ((byte & 0xF0) == 0xE0)
            {
                if ((current[1] & 0xC0) != 0x80 || (current[2] & 0xC0) != 0x80)
                    break;
                count++;
                current += 3;
            }
            // Special case: byte 0x85 is used as an escape to represent
            // a 3-character-wide glyph (e.g., fullwidth CJK character)
            else
            {
                // Advance past the escape byte
                current++;
                if (byte != 0x85)
                    break; // Unknown lead byte, abort
                count += 3; // Counts as three display characters
            }

            // Prevent scanning past end of string
            if (current >= end)
                break;
        }
    }

    // Return byte offset from start of string
    return (int)(current - str);
}