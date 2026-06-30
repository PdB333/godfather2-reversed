// FUNC_NAME: parseInt
// Address: 0x004d6d50
// Parses an integer from a string, skipping leading whitespace and optional sign.
// Returns true if any digits were parsed (or string was valid), false if null/empty.
// On success, result is stored in outValue (if non-null), else 0.
bool parseInt(const char* str, uint* outValue) {
    bool success = false;
    uint value = 0;

    if (str != nullptr && *str != '\0') {
        // skip whitespace
        while (*str == ' ' || *str == '\t' || *str == '\r' || *str == '\n')
            str++;

        int sign = 1;
        if (*str == '-') {
            sign = -1;
            str++;
        }

        char c = *str;
        while (c != '\0') {
            // check if digit (0-9)
            if ((uint)(c - '0') > 9)
                break; // stop on non-digit
            value = value * 10 + (c - '0');
            str++;
            c = *str;
        }
        value = sign * value;
        success = true;
    }

    if (outValue != nullptr) {
        // store value if success, else 0
        *outValue = success ? value : 0;
    }

    // Note: original function returns void, but success is implied by outValue.
    // We return bool for clarity.
    return success;
}