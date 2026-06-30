// FUNC_NAME: StringFormatter::formatCapturedArgs

void __thiscall StringFormatter::formatCapturedArgs(int this, char **outputPtr, void *captureData, int captureDataSize) {
    // +0x08: pointer to tokenizer/lexer state
    TokenizerState *tokenizer = *(TokenizerState **)(this + 8);
    // tokenizer->currentFormatToken: pointer to the format token (8-byte struct)
    int formatTokenAddr = tokenizer->field3; // tokenizer+0x0C? Actually piVar5[3]
    // tokenizer->outputEnd: end of current output buffer region?
    int *outputEnd = (int *)tokenizer->field2; // tokenizer+0x08? Actually piVar5[2]

    // Point to the token's data (type and value)
    int *tokenData = (int *)(formatTokenAddr + 0x10);

    // Check if current token is valid (type 4 = literal string, type 3 = capture)
    if ((tokenData < outputEnd) && (tokenData != NULL) && ((*tokenData == 4) || (*tokenData == 3))) {
        char *stringPtr;    // pointer to the string content
        char *stringEnd;    // end of the string content

        if (*tokenData == 4) {
            // Literal string token: get string from token's data + additional offset
            int literalData = *(int *)(formatTokenAddr + 0x14);
            stringPtr = (char *)(literalData + 0x10);
            stringEnd = *(char **)(literalData + 0x0C);
        } else { // type == 3
            // Capture token: need to validate and get string from capture data
            int isValid = FUN_00633990(tokenizer);
            if (isValid == 0) {
                stringPtr = NULL;
                stringEnd = NULL;
            } else {
                int captureOffset = *(int *)(formatTokenAddr + 0x14);
                stringPtr = (char *)(captureOffset + 0x10);
                stringEnd = *(char **)(captureOffset + 0x0C);
            }
            // Check if buffer needs flushing
            if (*(unsigned int *)(tokenizer->field4 + 0x20) <= *(unsigned int *)(tokenizer->field4 + 0x24)) {
                FUN_00627360(); // buffer flush
            }
        }
        // Iterate over the string characters
        if (stringPtr != NULL) {
            char *currentChar = stringPtr;
            while (currentChar < stringEnd) {
                if (*currentChar == '%') {
                    // Found format specifier
                    char nextChar = *(currentChar + 1);
                    currentChar++; // skip the '%' (will be incremented again)
                    if (isdigit((unsigned char)nextChar)) {
                        // Indexed capture: %1, %2, etc.
                        int captureIndex = nextChar - '1'; // 0-based
                        if ((captureIndex < 0) || (captureIndex >= *(int *)(this + 0x0C)) ||
                            (*(int *)(this + 0x14 + captureIndex * 8) == -1)) {
                            // Invalid capture index
                            FUN_00627bd0("invalid capture index");
                            goto error_handle;
                        }
                        // Format the captured argument
                        FUN_0062c150(); // prepare capture?
                        FUN_00628c50(); // write captured argument to output
                    } else {
                        // Literal character after % (escape)
                        if (((int *)*outputPtr + 0x83 <= *(int **)*outputPtr) && 
                            (FUN_00628940() != 0)) {
                            FUN_006289a0(outputPtr); // resize output buffer
                        }
                        *(*outputPtr) = nextChar; // write the character
                        (*outputPtr)++;
                    }
                } else {
                    // Regular character
                    if (((int *)*outputPtr + 0x83 <= *(int **)*outputPtr) && 
                        (FUN_00628940() != 0)) {
                        FUN_006289a0(outputPtr); // resize output buffer
                    }
                    *(*outputPtr) = *currentChar;
                    (*outputPtr)++;
                }
                currentChar++;
            }
        }
        return;
    }

error_handle:
    // Token type not recognized: copy raw token data and adjust tokenizer state
    *outputEnd = *tokenData;
    outputEnd[1] = tokenData[1];
    tokenizer->field2 = (int)outputEnd + 8; // advance output end
    int shiftAmount = FUN_0062c1b0(captureData, captureDataSize);
    FUN_006362d0(tokenizer, tokenizer->field2 - (shiftAmount * 8 + 8), 1);
    int *lastToken = (int *)(tokenizer->field2 - 8);
    if ((lastToken != NULL) && ((*lastToken == 4) || (*lastToken == 3))) {
        FUN_00628c50(); // re-evaluate capture?
        return;
    }
    tokenizer->field2 = (int)lastToken;
}