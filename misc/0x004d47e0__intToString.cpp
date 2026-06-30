// FUNC_NAME: intToString
// Address: 0x004d47e0
// Converts an integer to a string. Called with value in EAX and buffer pointer in ESI (__fastcall-like convention).
// Returns the length of the resulting string (excluding null terminator).

int __fastcall intToString(int value, char* buffer)
{
    int absoluteValue;             // iVar2
    int digitCount;                // iVar5
    int swapIndex;                 // iVar2 (reused)
    int lowIndex;                  // iVar3
    char currentChar;              // uVar1
    int tempIndex;                 // iVar4

    // Take absolute value for digit extraction
    if (value < 0) {
        absoluteValue = -value;
    } else {
        absoluteValue = value;
    }

    digitCount = 0;
    do {
        tempIndex = digitCount;
        absoluteValue = absoluteValue / 10;
        digitCount = digitCount + 1;
        buffer[tempIndex] = (char)((absoluteValue % 10) + '0');
        absoluteValue = absoluteValue / 10;
    } while (absoluteValue != 0);

    // Add minus sign if negative
    if (value < 0) {
        buffer[digitCount] = '-';
        digitCount = tempIndex + 2;  // tempIndex was (digitCount - 1) before increment
    }

    // Null terminate
    buffer[digitCount] = '\0';

    // Reverse the string (including sign if present)
    swapIndex = digitCount - 1;
    lowIndex = 0;
    if (0 < swapIndex) {
        do {
            currentChar = buffer[swapIndex];
            buffer[swapIndex] = buffer[lowIndex];
            buffer[lowIndex] = currentChar;
            lowIndex = lowIndex + 1;
            swapIndex = swapIndex - 1;
        } while (lowIndex < swapIndex);
    }

    return digitCount;
}