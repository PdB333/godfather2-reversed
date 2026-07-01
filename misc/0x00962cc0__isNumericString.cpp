// FUNC_NAME: isNumericString
// Address: 0x00962cc0
// Role: Validates that a string (with explicit length) contains only digits or '.' (decimal point).
// If the pointer is null, it defaults to a static empty string; empty string returns true (valid).
// Returns true (1) if all characters are digits or '.' or if string is empty; false (0) otherwise.

bool __cdecl isNumericString(const char* str, int length)
{
    const char* pcStart;
    const char* pcEnd;

    // Default to an empty string if null pointer
    if (str == nullptr) {
        str = (const char*)&DAT_0120546e; // Probably an empty string constant
    }

    pcStart = str;
    pcEnd = str + length;

    while (true) {
        // If we've reached or passed the end, all characters are valid
        if (pcEnd <= pcStart) {
            return true;
        }

        // Check if current character is a digit or decimal point
        if (!isdigit((int)*pcStart) && *pcStart != '.') {
            break;
        }

        pcStart++;
    }

    return false;
}