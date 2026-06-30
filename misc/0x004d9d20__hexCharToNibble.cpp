// FUNC_NAME: hexCharToNibble
int hexCharToNibble(void)
{
    char ch;
    // The input is in the x86 AL register (implicit parameter)
    // Returns the numeric value of a hex digit character (0-15), or -1 if invalid.
    if ('/' < ch) {  // '/', that is '0' - 1, so ch > '/'
        if ('`' < ch) {  // '`' is before 'a', so ch is lowercase
            ch = ch - 0x20;  // convert to uppercase
        }
        if (ch < 'G') {  // 'G' is after 'F', so valid hex char (0-9, A-F)
            if (ch < ':') {  // ':', that is '9' + 1, so digit
                return ch - '0';  // 0x30
            }
            if ('@' < ch) {  // '@' is 'A' - 1, so ch > '@' means uppercase letter
                return ch - 'A' + 10;  // 0x37, returns 10-15
            }
        }
    }
    return -1;  // invalid character
}