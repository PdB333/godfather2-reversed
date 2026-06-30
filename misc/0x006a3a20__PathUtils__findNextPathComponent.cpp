// FUNC_NAME: PathUtils::findNextPathComponent
// Address: 0x006a3a20
// Parses a wide-character string (UTF-16) using a helper to locate the next path component
// after an unescaped backslash delimiter. Handles backslash escaping (e.g., "\\" denotes literal backslash).
// Returns the index (in characters) of the start of the next component, or -1 on error.
// Data reference: DAT_00d5d624 likely contains a delimiter set or tokenization table.

int PathUtils::findNextPathComponent(short* str) // str is a pointer to UTF-16 string
{
    int index = 1; // Start at offset 1 (skip first character? Possibly leading '\\'?)

    while (true) {
        // Helper function: given current position and a delimiter table,
        // returns length of next token (or -1 if end/error)
        int tokenLen = FUN_006a37f0(str + index, &DAT_00d5d624);
        if (tokenLen < 0) {
            return -1;
        }
        index += tokenLen;

        bool oddBackslashes = false;
        // Check if character immediately before the delimiter is a backslash
        if (str[index - 1] != 0x5c) { // 0x5c = '\'
            break; // Not a backslash → normal component end
        }

        // Consecutive backslashes handling – count backwards from the delimiter
        short* cursor = &str[index - 1];
        do {
            oddBackslashes = !oddBackslashes;
            cursor--;
        } while (*cursor == 0x5c);

        if (oddBackslashes) {
            // Odd count → this backslash is an unescaped separator
            return index;
        }

        // Even count → the backslash is escaped; skip it and continue scanning
        index++;
        if (index == 0) {
            // Overflow / invalid state
            return -1;
        }
    }
    return index;
}