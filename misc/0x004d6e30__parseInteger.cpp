// FUNC_NAME: parseInteger
// Function address: 0x004d6e30
// Parses a string to an integer, supporting hexadecimal "0x" prefix.
// Returns 1 on success, 0 on failure. Output is stored in *outValue.
// Whitespace at start is skipped. Empty string sets *outValue = 0 and returns 1.

int parseInteger(const char* inputStr, int* outValue)
{
    int result = 0;
    
    // Handle null or empty string
    if ((inputStr == nullptr) || (*inputStr == '\0')) {
        if (outValue != nullptr) {
            *outValue = result;
        }
        return 1;
    }
    
    // Skip leading whitespace (space, tab, \r, \n)
    while ((*inputStr == ' ') || (*inputStr == '\t') || (*inputStr == '\r') || (*inputStr == '\n')) {
        inputStr++;
    }
    
    // Find end of string
    const char* end = inputStr;
    while (*end != '\0') {
        end++;
    }
    // end now points past the null terminator
    
    // Check for "0x" prefix (hexadecimal)
    int strLen = end - (inputStr + 1); // length excluding the first character? Actually inputStr+1 is second char.
    // Since inputStr+1 points to second char, end-(inputStr+1) = string length (since end is past null).
    if ((strLen > 2) && (*inputStr == '0')) {
        int secondChar = inputStr[1];
        // Convert to lowercase if uppercase
        if ((unsigned int)(secondChar - 0x41) < 0x1a) {  // 'A' to 'Z'
            secondChar += 0x20; // to lowercase
        }
        if (secondChar == 'x') {
            const char* hexPos = inputStr + 2;
            int hexDigits = end - (inputStr + 1) - 2; // number of hex digit chars
            if (hexDigits > 0x10) { // more than 16 hex digits -> overflow
                return 0;
            }
            char currentChar = *hexPos;
            while (currentChar != '\0') {
                int digitValue;
                // Convert to lowercase if uppercase
                if ((unsigned int)(currentChar - 0x41) < 0x1a) {
                    currentChar += 0x20;
                }
                // Digit 0-9
                if ((unsigned char)(currentChar - 0x30) < 10) {
                    digitValue = currentChar - 0x30;
                }
                // Hex letter a-f
                else if ((unsigned char)(currentChar + 0x9f) < 6) { // 0x9f = 159, so currentChar in 'a'..'f' (97-102)
                    digitValue = currentChar - 0x57; // 'a' -> 10, 'b' -> 11, ...
                }
                else {
                    return 0; // invalid character
                }
                if (digitValue < 0) {
                    return 0;
                }
                hexPos++;
                result = result * 0x10 + digitValue;
                currentChar = *hexPos;
            }
            if (outValue != nullptr) {
                *outValue = result;
            }
            return 1;
        }
    }
    
    // If not hex, fall back to decimal parsing (via external function)
    return FUN_004d6dd0(); // assumed to handle decimal conversion
}