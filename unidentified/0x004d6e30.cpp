// FUN_004d6e30: parseInteger
// Parses an integer string, supporting decimal (via helper) and hexadecimal (0x prefix, case-insensitive).
// Returns 1 on success with value stored in *outValue (if not null), 0 on failure.
// If str is null or empty, returns 1 and sets *outValue = 0.
int parseInteger(const char* str, int* outValue)
{
    int result = 0;

    // Handle null or empty string: succeed with 0
    if (str == nullptr || *str == '\0')
    {
        if (outValue != nullptr)
            *outValue = 0;
        return 1;
    }

    // Skip leading whitespace
    while (*str == ' ' || *str == '\t' || *str == '\r' || *str == '\n')
        ++str;

    // Check for hex prefix: 0x or 0X (case-insensitive)
    if (strlen(str) > 2 && str[0] == '0')
    {
        char second = str[1];
        // Convert to lowercase
        if (second >= 'A' && second <= 'Z')
            second += 0x20; // To lowercase
        if (second == 'x')
        {
            const char* hexStart = str + 2;
            size_t hexLen = strlen(hexStart);
            // Maximum 16 hex digits
            if (hexLen > 16)
                return 0;

            while (*hexStart != '\0')
            {
                char digit = *hexStart;
                // Convert uppercase to lowercase
                if (digit >= 'A' && digit <= 'Z')
                    digit += 0x20; // To lowercase

                if (digit >= '0' && digit <= '9')
                {
                    result = result * 16 + (digit - '0');
                }
                else if (digit >= 'a' && digit <= 'f')
                {
                    result = result * 16 + (digit - 'a' + 10);
                }
                else
                {
                    return 0; // Invalid hex digit
                }
                ++hexStart;
            }

            if (outValue != nullptr)
                *outValue = result;
            return 1;
        }
    }

    // Not hex – delegate to decimal parser (FUN_004d6dd0)
    return FUN_004d6dd0(); // This helper uses the same params (str, outValue) implicitly
}