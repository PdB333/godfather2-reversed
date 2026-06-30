// FUNC_NAME: parseInt

void parseInt(const char* str, int* outVal)
{
    // Skip leading whitespace
    while (*str == ' ' || *str == '\t' || *str == '\r' || *str == '\n')
        str++;

    int sign = 1;
    int result = 0;
    bool success = false;

    if (str != nullptr && *str != '\0')
    {
        sign = 1;
        // Check for minus sign
        if (*str == '-')
        {
            sign = -1;
            str++;
        }

        // Parse digits
        while (*str != '\0')
        {
            char ch = *str;

            // Check if character is a digit (0-9)
            if (ch < '0' || ch > '9')
            {
                // Non-digit encountered → stop parsing, but note: we don't set success if we've already parsed something?
                // The original code jumps to LAB_00697d1d which sets *outVal to 0 if success false, or to result*sign if true.
                // This goto means we exit the loop without setting success to true unless we finished the whole string.
                // Actually, the original loops while *str != '\0', and if a non-digit is found, it goes to LAB_00697d1d directly,
                // without setting success. So only if we make it to the null terminator without hitting a non-digit, we set success=true.
                // So a partial parse (e.g., "123abc") will not be considered successful.
                // In the reconstructed code, we break and then after loop we set success based on whether we broke early.
                break;
            }

            result = result * 10 + (ch - '0');
            str++;
        }

        // If we reached the end of the string (i.e., the loop exited because *str=='\0'), then parsing succeeded.
        if (*str == '\0')
            success = true;
    }

    if (outVal != nullptr)
    {
        if (success)
            *outVal = sign * result;
        else
            *outVal = 0;
    }
}