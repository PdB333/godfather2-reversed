// FUNC_NAME: itoa_wide (integer to wide string helper)
int __fastcall intToWideString(short* buffer) // integer value passed in EAX, buffer in ECX
{
    bool isNegative = false;
    int digitCount = 0;
    int value = in_EAX; // integer to convert (passed via EAX)

    if (value < 0) {
        isNegative = true;
        value = -value;
    }

    // Convert decimal digits to reversed wide string
    short localBuffer[32]; // enough for 32-bit int
    do {
        int index = digitCount;
        int quotient = value / 10;
        digitCount = index + 1;
        localBuffer[index] = (short)(value % 10) + 0x30; // '0' digit
        value = quotient;
    } while (value != 0);

    // If negative, add minus sign
    int resultLength = digitCount;
    if (isNegative) {
        localBuffer[digitCount] = 0x2d; // '-'
        digitCount = resultLength + 1;
        resultLength = digitCount;
    }

    // Copy reversed string to output buffer in correct order
    int i = digitCount;
    while (i = i - 1, i >= 0) {
        *buffer = localBuffer[i];
        buffer++;
    }
    *buffer = 0; // null terminator

    return resultLength;
}