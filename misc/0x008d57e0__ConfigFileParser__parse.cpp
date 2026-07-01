// FUNC_NAME: ConfigFileParser::parse
void __thiscall ConfigFileParser::parse(void *thisPtr, const char *configBuffer) {
    char hasMoreTokens;
    int tokenType;
    int tokenHandle; // handle/index for token
    const char *stringValue;

    // Initialize parser with the input buffer
    parserInit(configBuffer);
    // Set a specific parse key (hash 0x18e120d9) - likely for encryption or filter
    parserSetKey(configBuffer, 0x18e120d9);

    hasMoreTokens = parserHasMoreTokens();
    while (hasMoreTokens == 0) {
        // Read next token (advance parser)
        parserReadNextToken();

        tokenType = parserGetTokenType(); // returns 0..10
        switch (tokenType) {
        case 0: { // Token type: integer value? Store at +0x68
            tokenHandle = parserReadNextToken();
            *(int *)((char *)thisPtr + 0x68) = *(int *)(tokenHandle + 8);
            break;
        }
        case 1: { // Token type: string value, store at +0x50
            parserReadNextToken();
            stringValue = parserGetTokenString();
            copyStringToBuffer((char *)thisPtr + 0x50, stringValue);
            break;
        }
        case 2: { // Token type: string value, store at +0x58
            parserReadNextToken();
            stringValue = parserGetTokenString();
            copyStringToBuffer((char *)thisPtr + 0x58, stringValue);
            break;
        }
        case 3: { // Token type: string value, process via handleStringValue
            parserReadNextToken();
            stringValue = parserGetTokenString();
            handleStringValue(stringValue); // e.g., log or special handling
            break;
        }
        case 4: { // Token type: integer value, store at +0x94
            tokenHandle = parserReadNextToken();
            *(int *)((char *)thisPtr + 0x94) = *(int *)(tokenHandle + 8);
            break;
        }
        case 5: { // Token type: integer value, store at +0x8c
            tokenHandle = parserReadNextToken();
            *(int *)((char *)thisPtr + 0x8c) = *(int *)(tokenHandle + 8);
            break;
        }
        case 6: { // Token type: string value, process via handleStringValue
            parserReadNextToken();
            stringValue = parserGetTokenString();
            handleStringValue(stringValue);
            break;
        }
        case 7: { // Token type: integer value, store at +0x98
            tokenHandle = parserReadNextToken();
            *(int *)((char *)thisPtr + 0x98) = *(int *)(tokenHandle + 8);
            break;
        }
        case 8: { // Token type: integer value, store at +0x90
            tokenHandle = parserReadNextToken();
            *(int *)((char *)thisPtr + 0x90) = *(int *)(tokenHandle + 8);
            break;
        }
        case 9: { // Token type: integer value, store at +0x9c
            tokenHandle = parserReadNextToken();
            *(int *)((char *)thisPtr + 0x9c) = *(int *)(tokenHandle + 8);
            break;
        }
        case 10: { // Token type: integer value, store at +0xa0
            tokenHandle = parserReadNextToken();
            *(int *)((char *)thisPtr + 0xa0) = *(int *)(tokenHandle + 8);
            break;
        }
        }

        // Advance to next token/field
        parserAdvanceToken();
        hasMoreTokens = parserHasMoreTokens();
    }

    // If a global default data buffer exists, copy it to +0x3c (size 0x8000)
    if (globalDefaultDataBuffer != 0) {
        memcpy((char *)thisPtr + 0x3c, globalDefaultDataBuffer, 0x8000);
    }
}