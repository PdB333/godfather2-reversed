// FUNC_NAME: findTagEnd
// Address: 0x006a37b0
// Role: Parses a sequence of 16-bit characters (shorts) looking for a pattern: '?' ... '?' '>' 
// Returns the index (in shorts) after the '>' if found, -1 if pattern incomplete, -2 if first char not '?'
// Used for parsing tagged segments in wide strings (e.g., "?something?>")

int findTagEnd(const short* data)
{
    // Expect first character (at offset 2) to be '?' (0x3f)
    if (data[1] != 0x3f) {
        return -2;
    }

    int i;
    // Scan from index 2 (third short) until we find another '?' (0x3f)
    for (i = 2; data[i] != 0x3f; i++) {
        // empty loop body
    }

    // After the second '?', check if the next character is '>' (0x3e)
    if (data[i + 1] == 0x3e) {
        // Return index after the '>'
        return i + 2;
    }

    return -1;
}