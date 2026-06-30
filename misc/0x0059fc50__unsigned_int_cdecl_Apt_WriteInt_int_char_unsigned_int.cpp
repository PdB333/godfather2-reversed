// Xbox PDB: unsigned int __cdecl Apt_WriteInt(int,char *,unsigned int)
// FUNC_NAME: Apt::intToString
// Address: 0x0059fc50
// Role: Converts an integer to a decimal string with sign, returning the string length.
// File: source/Apt/Apt.cpp
// Note: Requires buffer size >= 13 (sizeof(revStr) check).

int Apt::intToString(uint originalValue, char* buffer, uint bufLen)
{
    // Assert buffer is large enough to hold the string (max 10 digits + sign + null)
    if (bufLen < 13) {
        // Debug assertion: "bufLen >= sizeof(revStr)"
        // The actual assert code (from decompiler) is omitted for brevity.
        // In debug builds, this triggers a break or log.
        __debugbreak(); // placeholder
    }

    bool negative = (int)originalValue < 0;
    uint value = negative ? -originalValue : originalValue;

    // Temporary buffer for reversed digits (max 10 digits for 32-bit int)
    char revStr[12];
    int digitCount = 0;

    do {
        uint digit = value % 10;
        revStr[digitCount] = (char)(digit + '0');
        value /= 10;
        digitCount++;
    } while (value != 0);

    char* writePtr = buffer;

    // Write sign if negative
    if (negative) {
        *writePtr = '-';
        writePtr++;
    }

    // Copy digits in correct order (reverse of revStr)
    for (int i = digitCount - 1; i >= 0; i--) {
        *writePtr = revStr[i];
        writePtr++;
    }

    // Null-terminate
    *writePtr = '\0';

    // Return length of string (excluding null)
    return (int)(writePtr - buffer);
}