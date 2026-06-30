// FUNC_NAME: compressValueToChar
// Address: 0x00644820
// Converts a numeric value into a single printable character for debug/log display.
// Splits the value into increasing bit ranges and maps to ASCII characters.
int compressValueToChar(uint value)
{
    // Check if value fits in 6-bit range (0-2111)
    if ((value >> 6) < 0x21)
        return (value >> 6) + 0x38; // '8' to 'X' (0x38-0x58)

    // Check if value fits in 9-bit range (0-10751)
    if ((value >> 9) < 0x15)
        return (value >> 9) + 0x5b; // '[' to 'o' (0x5b-0x6f)

    // Check if value fits in 12-bit range (0-45055)
    if ((value >> 12) < 0xb)
        return (value >> 12) + 0x6e; // 'n' to 'x' (0x6e-0x78)

    // Check if value fits in 15-bit range (0-163839)
    if ((value >> 15) < 5)
        return (value >> 15) + 0x77; // 'w' to '{' (0x77-0x7b)

    // Check if value fits in 18-bit range (0-786431)
    if ((value >> 18) < 3)
        return (value >> 18) + 0x7c; // '|' to '~' (0x7c-0x7e)

    // Default for values above ~786432
    return 0x7e; // '~'
}