// FUNC_NAME: Token::parseNumericString
void __fastcall Token::parseNumericString(uint *token)
{
    bool isPositive;
    int exponent;
    int exponentValue;
    char *p;
    char *p2;
    int digit;
    int temp;

    // Check if token type has the high bit set (bit 15)
    if ((uint8)(*token >> 15) == 1) {
        // Token type is stored in lower 15 bits
        switch (*token & 0x7FFF) {
        case 1:
            goto case1;
        default:
            break;
        case 5:
        case 6:
        case 7:
            return; // No parsing for these types
        }
    }
    return;

case1:
    // +0x0C: pointer to string to parse
    p = (char *)token[3];
    // Skip leading whitespace
    while (_isspace((int)*p) != 0) {
        p++;
    }
    // Check for sign
    isPositive = true;
    if (*p == '+') {
        p++;
    } else if (*p == '-') {
        isPositive = false;
        p++;
    }
    // Parse integer part digits
    while (_isdigit((int)*p) != 0) {
        p++;
    }
    // Parse optional fractional part
    if (*p == '.') {
        p++;
        while (_isdigit((int)*p) != 0) {
            p++;
        }
    }
    // Continue scanning digits (might be unnecessary)
    while (_isdigit((int)*p) != 0) {
        p++;
    }
    // Check for exponent (e/E)
    if (_tolower((int)*p) == 'e') {
        exponent = 1;
        char next = p[1];
        p2 = p + 1;
        if (_isdigit((int)next) == 0) {
            if (next == '-') {
                exponent = -1;
            }
            p2 = p + 2;
        }
        // Parse exponent digits
        exponentValue = 0;
        digit = (int)*p2;
        while (_isdigit(digit) != 0) {
            exponentValue = (digit - '0') + exponentValue * 10;
            digit = (int)p2[1];
            p2++;
        }
        if (exponent == -1) {
            exponentValue = -exponentValue;
        }
        // Adjust exponent to range -7..7 (ineffective loops)
        if (exponentValue < -7) {
            temp = (-exponentValue - 8U >> 3) + 1;
            exponentValue = exponentValue + temp * 8;
            do {
                temp--;
            } while (temp != 0);
        }
        if (exponentValue < 0) {
            temp = -exponentValue;
            exponentValue = 0;
            do {
                temp--;
            } while (temp != 0);
        }
        if (exponentValue > 7) {
            temp = ((exponentValue - 8U) >> 3) + 1;
            exponentValue = exponentValue + temp * (-8);
            do {
                temp--;
            } while (temp != 0);
        }
        // Loop to consume exponent digits (does nothing)
        for (; exponentValue > 0; exponentValue--) {
        }
    }
    // If sign was processed, return; else also return
    if (isPositive) {
        return;
    }
    return;
}