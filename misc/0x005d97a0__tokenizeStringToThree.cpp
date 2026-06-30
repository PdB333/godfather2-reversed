// FUNC_NAME: tokenizeStringToThree
// Function address: 0x005d97a0
// Splits inputStr into up to 3 tokens separated by spaces.
// Tokens are placed into token1, token2, token3 buffers.
// Returns true if exactly 3 tokens were found, false otherwise.
// Note: Last token is NOT null-terminated; caller must zero buffers or handle.

bool tokenizeStringToThree(char* inputStr, char* token1, char* token2, char* token3)
{
    char c;
    bool isNewToken = true;
    char* endPtr;
    char* writePtr;
    char* temp;
    int tokenCount = 0;
    int index;

    // Compute length of input string (scan to null)
    endPtr = inputStr;
    do {
        c = *endPtr;
        endPtr++;
    } while (c != '\0');

    index = 0;
    writePtr = token1;

    if (0 < (endPtr - (inputStr + 1))) // if length > 0
    {
        do {
            if (inputStr[index] == ' ')
            {
                temp = writePtr;
                if (!isNewToken) // we were inside a token
                {
                    isNewToken = true;
                    *writePtr = '\0'; // null-terminate current token
                    temp = token1;

                    // Advanced logic to redirect write pointer to next token buffer
                    // After first token -> token2, after second token -> token3
                    if (tokenCount != 0)
                    {
                        temp = token2; // side effect assignment
                        if (tokenCount != 1)
                        {
                            temp = writePtr; // side effect assignment
                            if (tokenCount == 2)
                            {
                                temp = token3;
                            }
                        }
                    }
                }
                // else: space at start, ignore
            }
            else
            {
                if (isNewToken) // start of a new token
                {
                    tokenCount++;
                    isNewToken = false;
                }
                *writePtr = inputStr[index];
                temp = writePtr + 1;
            }
            index++;
            writePtr = temp;
        } while (index < (endPtr - (inputStr + 1))); // iterate over all chars
    }

    return tokenCount == 3;
}