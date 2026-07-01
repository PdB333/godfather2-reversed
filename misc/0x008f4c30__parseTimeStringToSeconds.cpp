// FUNC_NAME: parseTimeStringToSeconds
// Address: 0x008f4c30
// Parses a time string in format HH:MM:SS (or similar with non-digit separators) and returns total seconds.
// Internal helper: FUN_008f3be0 (parseUint) parses an unsigned integer from string, updates pointer.

int parseTimeStringToSeconds(char **ppString)
{
    char *str = *ppString;
    unsigned short *puStr;
    int hours, minutes, seconds;

    // If string is null, use default string at DAT_00e2df14 (likely "00:00:00")
    if (str == 0) {
        str = (char *) &DAT_00e2df14;
    }

    // Parse hours: skip non-digit characters, then parse integer
    hours = parseUint(str, &str);
    while (9 < (unsigned short)str[0] - 0x30) {
        str++;
    }

    // Parse minutes
    minutes = parseUint(str, &str);
    while (9 < (unsigned short)str[0] - 0x30) {
        str++;
    }

    // Parse seconds
    seconds = parseUint(str, &str);

    // Return total seconds = seconds + (minutes + hours * 60) * 60
    return seconds + (minutes + hours * 60) * 60;
}