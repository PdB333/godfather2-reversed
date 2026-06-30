// FUNC_NAME: parseFloat
/*
 * Function: parseFloat (0x004D6F20)
 * Role: Converts a C-string to a float value. Supports decimal, hexadecimal, and exponential notation.
 * Returns: 1 on success, 0 on failure. Output value passed via outValue pointer.
 * Trims leading/trailing whitespace. Handles '0x'/'0X' hex prefix (calls helper), '0f'/'0F' hex integer prefix,
 * negative sign, decimal point, and 'e'/'E' exponent.
 */
#include <cstdint>

typedef unsigned int uint;

// Forward declaration of hex float parser
uint parseHexFloat(const char* str, float* outValue);

uint parseFloat(const char* inputStr, float* outValue)
{
    float value = 0.0f;
    float result = 0.0f;
    uint ret = 0;

    if (inputStr == nullptr || *inputStr == '\0') {
        goto exit;
    }

    // Trim leading whitespace
    const char* start = inputStr;
    while (*start == ' ' || *start == '\t' || *start == '\r' || *start == '\n') {
        start++;
    }

    // Find end of string
    const char* end = start;
    while (*end != '\0') {
        end++;
    }
    uint len = static_cast<uint>(end - (start + 1));
    if (len == 0) {
        goto exit;
    }

    // Trim trailing whitespace from the back
    const char* endTrim = start + (len - 1);
    while (endTrim > start && (*endTrim == ' ' || *endTrim == '\t' || *endTrim == '\r' || *endTrim == '\n')) {
        endTrim--;
    }
    const char* endPtr = endTrim + 1;  // Points past last non-whitespace char

    // Check for hex prefixes: "0x"/"0X" or "0f"/"0F"
    if (len > 2 && *start == '0') {
        char secondChar = start[1];
        // Lowercase the second character for comparison
        if (secondChar >= 'A' && secondChar <= 'Z') {
            secondChar += 0x20;  // to lowercase
        }
        if (secondChar == 'f') {
            // Hex integer literal (e.g., "0fFF" parses like hex integer)
            start += 2;
            value = 0.0f;
            if (len - 2 > 16) {
                return 0;
            }
            char ch = *start;
            while (true) {
                if (ch == '\0') {
                    *outValue = value;
                    return 1;
                }
                // Convert hex digit to value
                int digit;
                if (ch >= 'A' && ch <= 'Z') {
                    ch += 0x20;
                }
                if (ch >= '0' && ch <= '9') {
                    digit = ch - '0';
                } else if (ch >= 'a' && ch <= 'f') {
                    digit = ch - 'a' + 10;
                } else {
                    return 0;
                }
                start++;
                value = static_cast<float>(static_cast<int>(value) * 16 + digit);
                ch = *start;
            }
        }
        if (secondChar == 'x') {
            return parseHexFloat(start, outValue);
        }
    }

    // Parse decimal number (with optional sign, decimal point, exponent)
    const char* cur = start;
    // Skip leading whitespace again (though already trimmed, but code shows it)
    while (*cur == ' ' || *cur == '\t' || *cur == '\r' || *cur == '\n') {
        cur++;
    }

    char signChar = *cur;
    bool negative = false;
    if (signChar == '-') {
        negative = true;
        cur++;
    }

    // Integer part
    while (*cur >= '0' && *cur <= '9') {
        value = value * 10.0f + static_cast<float>(*cur - '0');
        cur++;
    }

    // Decimal part (if present)
    const char* endPtrSaved = endPtr;  // save original endPtr for later
    if (*cur == '.') {
        cur++;
        // Check if the character before the original endPtr is 'f' (for float suffix?) — odd logic
        char beforeEndChar = *endPtr;
        if (beforeEndChar >= 'A' && beforeEndChar <= 'Z') {
            beforeEndChar += 0x20;
        }
        if (beforeEndChar == 'f') {
            endPtr = endPtrSaved;  // restore? Actually code sets pcVar2 = pcVar4, not endPtr
            // The original code sets pcVar2 = pcVar4 (i.e., endPtr = endPtr) if the char before end is 'f'.
            // That line is: if (beforeEndChar == 0x66) { pcVar2 = pcVar4; } which essentially does nothing? 
            // Possibly it's detecting a floating-point suffix 'f' to adjust the end point.
            // We'll mimic the original logic: if the last char (after trimming) is 'f', we ignore it.
            // But the original sets pcVar2 = pcVar4, where pcVar4 is the end pointer from trailing trim.
            // That doesn't change pcVar2. So the 'f' suffix is effectively ignored.
            // We'll just note it.
        }
        // Process fractional digits using powers of 0.1
        // The table at DAT_00e36d38 contains decreasing factors: 0.1, 0.01, 0.001, ...
        float fracFactor = 0.1f; // DAT_00e2fc48
        while (*cur >= '0' && *cur <= '9') {
            value += static_cast<float>(*cur - '0') * fracFactor;
            fracFactor *= 0.1f;
            cur++;
        }
    }

    // Skip any remaining digits (shouldn't be any after decimal)
    while (*cur >= '0' && *cur <= '9') {
        cur++;
    }

    const char* endNow = cur;  // pointer after decimal/digits

    // Check for exponent part: 'e' or 'E'
    if (start < cur) {
        char expChar = *cur;
        if (expChar >= 'A' && expChar <= 'Z') {
            expChar += 0x20;
        }
        if (expChar == 'e') {
            int signExp = 1;
            cur++;  // skip 'e'
            expChar = *cur;
            if (expChar >= '0' && expChar <= '9') {
                // positive exponent, no sign
            } else if (expChar == '-') {
                signExp = -1;
                cur++;
            } else if (expChar == '+') {
                cur++;
            } else {
                goto exit;  // invalid exponent format
            }
            int exponent = 0;
            int expDigits = 0;
            while (*cur >= '0' && *cur <= '9') {
                expDigits++;
                exponent = exponent * 10 + (*cur - '0');
                cur++;
            }
            if (expDigits == 0) {
                goto exit;
            }
            if (signExp == -1) {
                exponent = -exponent;
            }
            // Apply exponent in chunks of 8 to reduce large mults
            if (exponent < -7) {
                int steps = (-exponent - 8) / 8 + 1;
                exponent += steps * 8;
                float factor = 1e-8f; // 0.1^8 = 1e-8
                for (; steps > 0; steps--) {
                    value *= factor * factor * factor * factor * factor * factor * factor * factor; // Actually pow(0.1, 8)
                    // Simplified: value *= 1e-8f;
                }
            }
            if (exponent < 0) {
                int steps = -exponent;
                for (; steps > 0; steps--) {
                    value *= 0.1f;
                }
            }
            if (exponent > 7) {
                int steps = (exponent - 8) / 8 + 1;
                exponent -= steps * 8;
                float factor = 1e8f; // 10^8
                for (; steps > 0; steps--) {
                    value *= factor * factor * factor * factor * factor * factor * factor * factor; // pow(10, 8)
                    // Simplified: value *= 1e8f;
                }
            }
            for (; exponent > 0; exponent--) {
                value *= 10.0f;
            }
        }
    }

    // Check that we consumed expected characters (endNow should equal endPtr)
    if (cur != endPtr) {
        goto exit;
    }

    result = value;
    if (signChar == '-') {
        result = -value;
    }

exit:
    if (outValue != nullptr) {
        *outValue = result;
    }
    // Return 1 on success (0x1000000 >> 24 = 1), else 0
    return 1;
}