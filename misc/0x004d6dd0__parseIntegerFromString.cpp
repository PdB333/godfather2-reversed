// FUNC_NAME: parseIntegerFromString
void __fastcall parseIntegerFromString(const char* str, unsigned int* outValue)
{
    unsigned int value = 0;
    int success = 0;

    if (str != 0 && *str != '\0')
    {
        // skip leading whitespace
        while (*str == ' ' || *str == '\t' || *str == '\r' || *str == '\n')
        {
            str++;
        }

        char c = *str;
        if (c != '\0')
        {
            success = 1;
            while (c != '\0')
            {
                // check if character is a digit (0-9)
                if ((unsigned int)(c - '0') > 9)
                {
                    break; // stop at first non-digit
                }
                value = value * 10 + (c - '0');
                str++;
                c = *str;
            }
        }
    }

    // store result if output pointer is valid
    if (outValue != 0)
    {
        *outValue = success ? value : 0;
    }
}