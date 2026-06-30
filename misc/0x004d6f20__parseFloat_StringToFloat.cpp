// FUNC_NAME: parseFloat_StringToFloat
// Function address: 0x004d6f20
// Role: Custom string-to-float converter with support for hex, octal? (0f prefix), scientific notation, and leading/trailing whitespace trimming.
// Returns 1 on success, 0 on failure.

uint parseFloat(const char* inputStr, float* outValue)
{
    float result = 0.0f;
    uint successFlag = 0; // uStack_4, used to compute return value

    if ((inputStr != nullptr) && (*inputStr != '\0'))
    {
        // Trim leading whitespace
        const char* trimmedStart = inputStr;
        while (*trimmedStart == ' ' || *trimmedStart == '\t' || *trimmedStart == '\r' || *trimmedStart == '\n')
        {
            ++trimmedStart;
        }

        // Calculate length of the trimmed string (excluding leading spaces)
        const char* end = trimmedStart;
        while (*end != '\0')
            ++end;
        uint strLen = (uint)(end - (trimmedStart + 1)); // length excluding terminator? Actually this gives number of chars after trimmedStart up to but not including the null
        if (strLen == 0)
            goto failure;

        // Trim trailing whitespace
        const char* trimEnd = trimmedStart + (strLen - 1);
        while ((*trimEnd == ' ' || *trimEnd == '\t' || *trimEnd == '\r' || *trimEnd == '\n') && (trimmedStart < trimEnd))
        {
            --trimEnd;
        }
        const char* afterTrailingTrim = trimEnd + 1; // points to one past the last non-whitespace char

        // Check for '0' prefix (hex, octal, or custom 0f hex float)
        const char* curPos = trimmedStart;
        if ((strLen > 2) && (*trimmedStart == '0'))
        {
            int nextChar = (int)trimmedStart[1];
            // Convert to lowercase if uppercase letter
            int lowerNext = nextChar;
            if ((uint)(nextChar - 0x41) < 0x1a) // 'A' to 'Z'
                lowerNext = nextChar + 0x20;
            if (lowerNext == 0x66) // 'f' -> 0f prefix for hex float? (e.g., 0f1A)
            {
                curPos = trimmedStart + 2;
                result = 0.0f;
                if (strLen - 2 > 0x10) // more than 16 hex digits? return failure
                    return 0;
                // Parse hex digits until end of string
                char c = *curPos;
                while (true)
                {
                    if (c == '\0')
                    {
                        *outValue = result;
                        return 1;
                    }
                    // Convert to lowercase
                    if ((uint)(c - 0x41) < 0x1a)
                        c = c + 0x20;
                    if ((uint)(c - 0x30) < 10) // digit 0-9
                    {
                        int digit = c - 0x30;
                        result = result * 16.0f + (float)digit;
                    }
                    else
                    {
                        if ((uint)(c + 0x9f) > 5) // check if it's 'a'-'f' (c-0x61 <=5) => c+0x9f <=0x64? Actually condition: (byte)(c - 0x57) < 6? Hard to interpret; but return 0 if invalid
                            return 0;
                        int digit = c - 0x57; // 'a'->10, etc.
                        result = result * 16.0f + (float)digit;
                    }
                    ++curPos;
                    c = *curPos;
                }
            }
            // Check for '0x' prefix -> call hex parser (FUN_004d6e30)
            if ((uint)(nextChar - 0x41) < 0x1a)
                nextChar = nextChar + 0x20;
            if (nextChar == 0x78) // 'x'
            {
                return FUN_004d6e30(trimmedStart, outValue); // external hex-to-float function
            }
        }

        // Now handle decimal/scientific notation
        // Skip leading whitespace again (unnecessary but preserved)
        while (*curPos == ' ' || *curPos == '\t' || *curPos == '\r' || *curPos == '\n')
        {
            ++curPos;
        }

        // Check for sign
        char signChar = *curPos;
        bool negative = false;
        if (signChar == '-')
        {
            negative = true;
            ++curPos;
        }
        else if (signChar == '+')
        {
            ++curPos;
        }

        // Parse integer part: digits before decimal point
        while ((uint)(*curPos - 0x30) < 10)
        {
            int digit = (int)(*curPos - 0x30);
            result = result * 10.0f + (float)digit;
            ++curPos;
        }

        const char* backupPos = afterTrailingTrim; // used later for 'e' exponent? Actually this is the end of the trimmed string

        // Parse fractional part if decimal point present
        if (*curPos == '.')
        {
            // Check if the last character (after trailing trim) is 'f'? Actually they check if the char at trimEnd is 'f' (case insensitive)
            int lastChar = (int)*trimEnd;
            if ((uint)(lastChar - 0x41) < 0x1a)
                lastChar = lastChar + 0x20;
            const float* powerTable = (const float*)&DAT_00e36d38; // table of decreasing powers of 10: {0.1, 0.01, 0.001, ...}
            float currentPower = DAT_00e2fc48; // 0.1f
            while (true)
            {
                ++curPos;
                backupPos = afterTrailingTrim; // not sure why, but preserve
                if ((uint)(*curPos - 0x30) >= 10) // non-digit
                    break;
                float addValue = (float)(int)(*curPos - 0x30) * currentPower;
                currentPower = *(powerTable + 1); // next power, e.g., 0.01
                powerTable = powerTable + 1;
                result += addValue;
            }
        }

        // Skip any remaining digits (if number had no decimal, but there are trailing digits? Actually after decimal parsing, we skip digits)
        while ((uint)(*curPos - 0x30) < 10)
        {
            ++curPos;
        }

        const char* exponentStart = curPos; // current position after integer/fractional part

        // Check for exponent 'e' or 'E'
        if (backupPos < curPos) // if we moved past the end? Actually backupPos is the trimmed end pointer; this condition seems off
        {
            int expChar = (int)*curPos;
            if ((uint)(expChar - 0x41) < 0x1a)
                expChar = expChar + 0x20;
            if (expChar == 0x65) // 'e'
            {
                int exponent = 0;
                int expSign = 1;
                int expDigits = 0;
                curPos = curPos + 1;
                // Check for sign after 'e'
                int nextChar = (int)*curPos;
                if ((uint)(nextChar - 0x30) >= 10) // not a digit
                {
                    if (nextChar == 0x2d) // '-'
                    {
                        expSign = -1;
                        curPos = curPos + 1;
                    }
                    else if (nextChar == 0x2b) // '+'
                    {
                        curPos = curPos + 1;
                    }
                }
                // Parse exponent digits
                while ((uint)(*curPos - 0x30) < 10)
                {
                    expDigits++;
                    exponent = *curPos - 0x30 + exponent * 10;
                    ++curPos;
                }
                if (expDigits == 0)
                    goto failure;

                if (expSign == -1)
                    exponent = -exponent;

                // Scale result by 10^exponent
                if (exponent < -7)
                {
                    int bigNeg = (-exponent - 8) >> 3;
                    int remaining = exponent + bigNeg * 8;
                    // Multiply by 10^8 repeatedly
                    for (; bigNeg > 0; bigNeg--)
                    {
                        result = result * 0.1f * 0.1f * 0.1f * 0.1f * 0.1f * 0.1f * 0.1f * 0.1f;
                    }
                    // Apply remaining negative exponent
                    for (int i = 0; i < -remaining; i++)
                    {
                        result = result * 0.1f;
                    }
                }
                else if (exponent < 0)
                {
                    int absExp = -exponent;
                    for (int i = 0; i < absExp; i++)
                    {
                        result = result * 0.1f;
                    }
                }
                else if (exponent > 7)
                {
                    int bigPos = (exponent - 8) >> 3;
                    int remaining = exponent - bigPos * 8;
                    for (; bigPos > 0; bigPos--)
                    {
                        result = result * 10.0f * 10.0f * 10.0f * 10.0f * 10.0f * 10.0f * 10.0f * 10.0f;
                    }
                    for (int i = 0; i < remaining; i++)
                    {
                        result = result * 10.0f;
                    }
                }
                else
                {
                    for (int i = 0; i < exponent; i++)
                    {
                        result = result * 10.0f;
                    }
                }
            }
        }

        // Check if we parsed to the end of the string (excluding trailing whitespace)
        if (curPos != afterTrailingTrim)
            goto failure;

        // Apply sign
        float finalResult;
        if (negative)
            finalResult = -result;
        else
            finalResult = result;

        successFlag = 0x1000000; // prepare to return 1
    }

failure:
    if (outValue != nullptr)
        *outValue = finalResult; // finalResult might be uninitialized here? Actually it's set in the success path
    return successFlag >> 0x18; // successFlag initialized to 0, so failure returns 0; success path sets to 1
}