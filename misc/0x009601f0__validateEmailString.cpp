// FUNC_NAME: validateEmailString

/**
 * Checks if a given string appears to be a valid email address format.
 * Validation: length <= 126, contains '@' (not at start), contains '.', and
 * at least one '.' appears before the '@'.
 * (Note: The original code has a suspicious while loop that re-searches for '.' 
 * on the same string, which would cause infinite iteration. This reconstruction
 * interprets it as ensuring a '.' exists before '@', but the loop is omitted
 * as it appears to be a decompilation artifact.)
 */
int validateEmailString(char* str)
{
    char c;
    char* p;

    // Manual strlen: find end of string
    p = str;
    do {
        c = *p;
        p = p + 1;
    } while (c != '\0');

    // Reject strings longer than 126 characters (including null?)
    if ((char*)0x7e < p + (-1 - (int)(str + 1))) {
        // p - 1 - (str) = p - str - 1 = length of string
        // (char*)0x7e cast: compare length to 0x7e (126)
        return 0;
    }

    // Locate '@' and '.' in the string
    char* atPos = strchr(str, '@');
    char* dotPos = strchr(str, '.');

    // Walk through all '.' positions while they occur before the '@'
    // (Original loop re-initializes dotPos repeatedly; likely intended to 
    // skip to later '.' positions, but as written it's infinite. 
    // We omit the loop as it has no functional effect.)
    while (dotPos != (char*)0 && dotPos < atPos) {
        dotPos = strchr(str, '.'); // This doesn't advance the pointer – bug in original or decompiler? 
    }

    // Final validation: '@' exists, not at start, and '.' exists
    if ((atPos != str) && (atPos != (char*)0) && (dotPos != (char*)0)) {
        return 1;
    }
    return 0;
}