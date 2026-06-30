// FUNC_NAME: parseTokenList
// Address: 0x004d8380
// Role: Token parser for comma-separated values with parenthesis nesting and quoting support.
// Parses a string, extracting tokens separated by commas at depth 0, handling quoted strings and parentheses.
// Returns 1 if a closing parenthesis was encountered (at depth 0 or 1), otherwise 0.
// Modifies the input string pointer to point past the parsed portion.

char parseTokenList(char **inputString, int unused, bool trimWhitespace)
{
    char *currentChar = *inputString;
    char curChar = *currentChar;
    int parenDepth = 0;
    char foundClosingParen = '\0';
    
    bool bVar1 = false; // flag to skip further token extraction when closing paren at depth 0
    bool quoteActive = false;
    
    int tokenCount = 0;
    int tokenCapacity = 0;
    int tokenListBase = 0; // pointer to base of token storage (opaque)
    
    int local_28 = 0; // used for temporary depth storage?
    int local_10[3]; // callback-related (function pointer stored elsewhere)
    void (*callbackFunc)(); // not initialized in decompiled code, likely class member
    
    char *tokenStart = currentChar;
    char *tokenEnd = nullptr;
    
    if (curChar == '\0') {
        goto cleanup;
    }
    
    char *scanPtr = currentChar - 1;
    char *currentTokenStart = currentChar; // token start after last delimiter
    
    for (;;) {
        if (bVar1) {
            goto loopEnd;
        }
        
        if (!quoteActive) {
            tokenEnd = nullptr;
            char *localVar9 = currentTokenStart;
            
            if (quoteActive) {
                // inside quotes state is handled separately
            } else {
                if (curChar == ',') {
                    tokenEnd = scanPtr;
                    if (parenDepth != 1) goto processLoop;
                    // if depth is 1, fall through to token extraction
                    tokenEnd = scanPtr; // already set
                }
                
                if (curChar == '(') {
                    if (parenDepth == 0) {
                        currentTokenStart = scanPtr + 2; // start after '('
                    }
                    local_28 = parenDepth + 1;
                    parenDepth = local_28;
                    // local_28 is used later
                    goto processLoop;
                }
                
                if (curChar == ')') {
                    if (parenDepth == 0) {
                        // a closing paren at top level: extract token and stop
                        bVar1 = true;
                        // set tokenEnd? The code goes to LAB_004d8469 then LAB_004d83e9
                        foundClosingParen = '\x01';
                        tokenEnd = scanPtr;
                        goto extractToken;
                    } else if (parenDepth == 1) {
                        foundClosingParen = '\x01';
                        tokenEnd = scanPtr;
                        // extract token
                        goto extractToken; // through LAB_004d8469 -> LAB_004d83e9
                    }
                    parenDepth--;
                    local_28 = parenDepth;
                }
                
                if (curChar == '\"') {
                    quoteActive = true;
                }
            }
            
processLoop:
            // continue to next character
        }
        
loopEnd:
        curChar = currentChar[1];
        currentChar++;
        scanPtr++;
        currentTokenStart = tokenStart; // restore? Actually tokenStart may change
        if (curChar == '\0') goto finalize;
    }
    
extractToken:
    if (tokenEnd == nullptr) goto processLoop;
    // Trim whitespace if required
    char *start = currentTokenStart;
    char *end = tokenEnd;
    if (trimWhitespace) {
        // trim leading whitespace
        while (start < end) {
            char c = *start;
            if (c != ' ' && c != '\t' && c != '\n' && c != '\r') break;
            start++;
        }
        // trim trailing whitespace
        while (end > start) {
            char c = *(end - 1);
            if (c != ' ' && c != '\t' && c != '\n' && c != '\r') break;
            end--;
        }
    }
    // If start >= end, token is empty
    if (start < end) {
        // store token: FUN_004d3f10(start, 0, end - start) possibly copies string
        FUN_004d3f10(start, 0, end - start);
    }
    
    // Grow token list if needed
    if (tokenCount == tokenCapacity) {
        int newSize = (tokenCapacity == 0) ? 1 : tokenCapacity * 2;
        // reallocate tokenListBase
        FUN_00407880(newSize); // this likely resizes some global array
    }
    
    // Add token to list (store pointer/size)
    // FUN_004d3b50(local_10) is called? In decompiled: iVar6 = local_18 * 0x10; then FUN_004d3b50(local_10)
    // It seems to store the token info.
    int offset = tokenCount * 0x10; // 16 bytes per token entry
    tokenCount++;
    if (offset + tokenListBase != 0) {
        FUN_004d3b50(local_10); // probably stores this token in the list
    }
    
    // Invoke callback if present
    if (local_10[0] != 0) {
        callbackFunc = (void (*)())local_10[0];
        callbackFunc(local_10[0]);
    }
    
    goto processLoop;
    
cleanup:
    FUN_00407430(); // cleanup
    return foundClosingParen;
    
finalize:
    if (foundClosingParen != '\0') {
        if (tokenCount == 1 && *(int *)(tokenListBase + 4) == 0) {
            // Single token with empty data? (likely a specific case)
            FUN_004d8a00();
        } else {
            FUN_004d8a60(&tokenListBase);
        }
        *inputString = currentChar; // update input string pointer
    }
    goto cleanup;
}