// FUNC_NAME: hexCharToInt
// Function address: 0x004d9d20
// Converts a hexadecimal character (0-9, A-F, a-f) to its integer value (0-15).
// Returns -1 if the character is not a valid hex digit.
int hexCharToInt(char c)
{
    // Convert lowercase to uppercase
    if (c > '`') {
        c -= 0x20;
    }

    // Check if it's a digit (0-9) or uppercase letter (A-F)
    if (c < 'G') {
        if (c < ':') {
            // Digit: '0' - '9'
            return c - '0';
        }
        if (c > '@') {
            // Uppercase letter: 'A' - 'F'
            return c - 0x37; // 0x37 = 55, so 'A' - 55 = 10
        }
    }

    // Invalid hex character
    return -1;
}