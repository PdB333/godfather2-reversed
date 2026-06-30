// FUNC_NAME: parseThreeTokenCommand
// Address: 0x005d97a0
// Parses a space-delimited command string into up to three tokens.
// Returns true if exactly three tokens are present, false otherwise.
// Tokens are written into outToken1, outToken2, outToken3 and null-terminated
// (except possibly the last token if the input doesn't end with a space).
bool parseThreeTokenCommand(const char* input, char* outToken1, char* outToken2, char* outToken3) {
    int tokenIndex = 0;
    bool atStartOfToken = true; // true when next non-space starts a new token
    char* src = (char*)input;

    // Compute length of input string (strlen behavior)
    char* end;
    end = src;
    while (*end != '\0') end++;
    int length = (int)(end - input);

    char* currentOut = outToken1;

    for (int i = 0; i < length; ++i) {
        char c = input[i];
        if (c == ' ') {
            if (!atStartOfToken) {
                // End of current token: null-terminate and advance to next output buffer
                atStartOfToken = true;
                *currentOut = '\0';
                // Select next output buffer based on token index (1-based)
                if (tokenIndex == 1) {
                    currentOut = outToken2;
                } else if (tokenIndex == 2) {
                    currentOut = outToken3;
                }
                // For tokenIndex > 2, currentOut remains where it is (no more buffers)
            }
            // else: consecutive space, ignore
        } else {
            if (atStartOfToken) {
                tokenIndex++;
                atStartOfToken = false;
            }
            // Copy character to current output buffer
            *currentOut = c;
            currentOut++;
        }
    }

    return tokenIndex == 3;
}