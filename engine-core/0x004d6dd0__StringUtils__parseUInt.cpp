// FUNC_NAME: StringUtils::parseUInt
// Function at 0x004d6dd0 – Parses an unsigned integer from a string, skipping leading whitespace.
// Returns true if entire string (after whitespace) consists of digits and is fully consumed,
// otherwise returns false and writes 0 to output. Uses ECX as unused this, EDX as string,
// and EDI as output pointer (reconstructed as a third parameter for clarity).

class StringUtils {
public:
    // Parses an unsigned integer from a string. Skips leading whitespace.
    // If the string contains only digits, sets *outValue to the parsed number and returns true.
    // Otherwise sets *outValue to 0 and returns false.
    // Note: The original assembly uses ECX (unused), EDX (str), EDI (outValue).
    // This reconstruction uses a standard method signature.
    bool parseUInt(const char* str, unsigned int* outValue) const {
        unsigned int value = 0;
        bool success = false;

        // If string is null or empty, fail immediately
        if (str == nullptr || *str == '\0') {
            goto done;
        }

        // Skip leading whitespace
        while (*str == ' ' || *str == '\t' || *str == '\r' || *str == '\n') {
            str++;
        }

        char c = *str;
        while (c != '\0') {
            // Check if character is a digit (0-9)
            if (c < '0' || c > '9') {
                goto done; // Non-digit encountered – abort conversion
            }
            value = (c - '0') + value * 10;
            str++;
            c = *str;
        }

        // Entire string was numeric
        success = true;

    done:
        if (outValue != nullptr) {
            *outValue = success ? value : 0;
        }
        return success;
    }
};