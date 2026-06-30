// FUN_NAME: PatternMatcher::matchPattern
int PatternMatcher::matchPattern(PatternContext* context) {
    int* inputPtr = *(int**)(context + 0xC); // +0xC: current input token pointer
    int* inputEnd = *(int**)(context + 0x8); // +0x8: current output token pointer
    int* tokenData;
    int startOffset = 0;
    int inputSize = 0;
    char* patternStr = nullptr;
    int patternLen = 0;

    // Read first token (likely a start offset or type)
    if ((inputPtr < inputEnd) && (inputPtr != nullptr)) {
        if (*inputPtr == 4) {
            startOffset = inputPtr[1] + 16; // 16? maybe a base offset
        } else {
            int isValid = isValidToken(context); // FUN_00633990
            if (isValid != 0) {
                startOffset = inputPtr[1] + 16;
            } else {
                startOffset = 0;
            }
            // Check if stack overflow?
            if (*(uint*)(*(int*)(context + 0x10) + 0x20) <= *(uint*)(*(int*)(context + 0x10) + 0x24)) {
                reportStackOverflow(); // FUN_00627360
            }
        }
        if (startOffset == 0) goto error;
    } else {
error:
        reportError("string"); // FUN_00627ac0(PTR_s_string_00e2a8ac)
    }

    // Read second token (likely length of input)
    inputPtr = *(int**)(context + 0xC);
    if ((inputPtr < inputEnd) && (inputPtr != nullptr)) {
        if (*inputPtr == 4) {
            inputSize = *(uint*)(inputPtr[1] + 0xC);
        } else {
            int isValid = isValidToken(context);
            if (isValid != 0) {
                inputSize = *(uint*)(inputPtr[1] + 0xC);
            } else {
                inputSize = 0;
            }
        }
    } else {
        inputSize = 0;
    }

    // Read third token (pattern string pointer)
    int tokenPos = *(int*)(context + 0xC);
    int* tokenTypePtr = (int*)(tokenPos + 8);
    if ((tokenTypePtr < inputEnd) && (tokenTypePtr != nullptr)) {
        if (*tokenTypePtr == 4) {
            patternStr = (char*)(*(int*)(tokenPos + 0xC) + 16);
        } else {
            int isValid = isValidToken(context);
            if (isValid != 0) {
                patternStr = (char*)(*(int*)(tokenPos + 0xC) + 16);
            } else {
                patternStr = (char*)0x0;
            }
            if (*(uint*)(*(int*)(context + 0x10) + 0x20) <= *(uint*)(*(int*)(context + 0x10) + 0x24)) {
                reportStackOverflow();
            }
        }
        if (patternStr != nullptr) goto got_pattern;
    }
    patternStr = (char*)0x2; // Placeholder? Actually 0x2 seems like an index
    reportError("string");
got_pattern:

    // Read fourth token (pattern length)
    int tokenPos2 = *(int*)(context + 0xC);
    int* tokenTypePtr2 = (int*)(tokenPos2 + 8);
    if ((tokenTypePtr2 < inputEnd) && (tokenTypePtr2 != nullptr)) {
        if (*tokenTypePtr2 == 4) {
            patternLen = *(int*)(*(int*)(tokenPos2 + 0xC) + 0xC);
        } else {
            int isValid = isValidToken(context);
            if (isValid != 0) {
                patternLen = *(int*)(*(int*)(tokenPos2 + 0xC) + 0xC);
            } else {
                patternLen = 0;
            }
        }
    } else {
        patternLen = 0;
    }

    // Read fifth token (maybe a float/flag)
    int* tokenPtr = (int*)(*(int*)(context + 0xC) + 16);
    float floatValue = 0.0f;
    if (((tokenPtr < inputEnd) && (tokenPtr != nullptr)) && (*tokenPtr > 0)) {
        floatValue = getFloatFromToken(tokenPtr); // FUN_00628080 (returns XMM0)
    }

    int intOffset = (int)floatValue;
    if (intOffset < 0) {
        intOffset = inputSize + 1 + intOffset; // Negative offset means from end?
    }
    uint searchEnd = (uint)(intOffset - 1);
    if ((int)searchEnd < 0) {
        searchEnd = 0;
    } else if (inputSize < searchEnd) {
        searchEnd = inputSize;
    }

    // Check if pattern has regex special characters
    int* regexCheckPtr = (int*)(*(int*)(context + 0xC) + 24);
    bool noRegex = false;
    if ((((regexCheckPtr < inputEnd) && (regexCheckPtr != nullptr)) &&
        ((*regexCheckPtr != 0 && ((*regexCheckPtr != 1 || (*(int*)(*(int*)(context + 0xC) + 28) != 0)))))) ||
        (_strpbrk(patternStr, "^$*+?.([%-") == nullptr)) {
        noRegex = true;
    }

    if (noRegex) {
        // Literal match
        int matchPos = literalMatch(startOffset + searchEnd, inputSize - searchEnd, patternStr, patternLen); // FUN_0062c050
        if (matchPos != 0) {
            int* output = *(int**)(context + 8);
            *output = 3;               // Token type: 3 = match result
            output[1] = (float)((matchPos - startOffset) + 1); // 1-based position?
            *(int*)(context + 8) = *(int*)(context + 8) + 8;
            output = *(int**)(context + 8);
            patternLen = (matchPos - startOffset) + patternLen;
            float fTmp = (float)patternLen;
            *output = 3;
            if (patternLen < 0) {
                fTmp = fTmp + 0x1p+10; // DAT_00e44578? Possibly a rounding constant
            }
            output[1] = fTmp;          // End offset (absolute)
            *(int*)(context + 8) = *(int*)(context + 8) + 8;
            return 2;                  // Match found
        }
    } else {
        // Regex match
        char* p = patternStr;
        bool anchored = false;
        if (*p == '^') {
            anchored = true;
            p++;
        }
        uint maxPos = inputSize + startOffset;
        int stackVar = context;
        int currentStart = startOffset;
        uint pos = searchEnd + startOffset;
        do {
            int regResult = regexMatch(&currentStart, pos, p); // FUN_0062bd60
            if (regResult != 0) {
                int* output = *(int**)(context + 8);
                *output = 3;
                output[1] = (float)(int)((pos - startOffset) + 1); // 1-based start?
                *(int*)(context + 8) = *(int*)(context + 8) + 8;
                output = *(int**)(context + 8);
                *output = 3;
                output[1] = (float)(regResult - startOffset); // end offset?
                *(int*)(context + 8) = *(int*)(context + 8) + 8;
                int extra = regexExtraFlags(0, 0); // FUN_0062c1b0
                return extra + 2;
            }
        } while ((pos < maxPos) && (pos = pos + 1, !anchored));
    }

    // No match
    **(int**)(context + 8) = 0;        // Token type 0 (failure)
    *(int*)(context + 8) = *(int*)(context + 8) + 8;
    return 1; // No match
}