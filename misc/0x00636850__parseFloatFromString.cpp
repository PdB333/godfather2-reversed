// FUNC_NAME: parseFloatFromString
// 0x00636850 - Parses a float from a string, returning 1 on success, 0 on failure.
// Skips leading whitespace, then converts the remaining numeric characters to a float.
// The converted value is stored in the output parameter.
// Returns 0 if the string is empty or contains non-numeric characters after whitespace.
int parseFloatFromString(float *outValue)
{
    float convertedValue;
    char *currentChar;

    convertedValue = (float)FUN_00b9ec18(); // Likely a string-to-float conversion function (e.g., atof, strtod)
    if (currentChar != (char *)unaff_ESI) {
        // Skip leading whitespace
        while (_isspace((int)*currentChar) != 0) {
            currentChar = currentChar + 1;
        }
        // Check if we reached the end of the string (all whitespace)
        if (*currentChar == '\0') {
            *outValue = convertedValue;
            return 1;
        }
    }
    return 0;
}