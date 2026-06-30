// FUNC_NAME: ScriptParser::expectToken
void __thiscall ScriptParser::expectToken(int lineNumber)
{
    // iVar1 points to a token node structure (likely a linked list or stack)
    int tokenNode = *(int *)(this + 0x1c);
    
    // Advance to next token (skip whitespace/comments?)
    advanceToken();
    
    // Handle token type 0x105 (possibly multi-line comment or block start)
    if (*(int *)(this + 0xc) == 0x105) {
        do {
            // Mark node as invalid (-1)
            *(int *)(tokenNode + 0x20) = -1;
            // Log warning with constant 0x7fff94 and a string from token data
            logWarning(0x7fff94, *(int *)(*(int *)(tokenNode + 0xc) + 8));
            // Free token node twice (likely reference counting)
            freeTokenNode(tokenNode);
            freeTokenNode(tokenNode);
            // Update node's previous pointer
            *(int *)(tokenNode + 0x1c) = *(int *)(tokenNode + 0x18);
            // Free again
            freeTokenNode(tokenNode);
            // Advance to next token
            advanceToken();
        } while (*(int *)(this + 0xc) == 0x105);
    }
    
    // Handle token type 0x104 (possibly single-line comment or block end)
    if (*(int *)(this + 0xc) == 0x104) {
        // Similar cleanup
        *(int *)(tokenNode + 0x20) = -1;
        logWarning(0x7fff94, *(int *)(*(int *)(tokenNode + 0xc) + 8));
        freeTokenNode(tokenNode);
        freeTokenNode(tokenNode);
        *(int *)(tokenNode + 0x1c) = *(int *)(tokenNode + 0x18);
        freeTokenNode(tokenNode);
        // Save previous token type
        *(int *)(this + 8) = *(int *)(this + 4);
        // Check if saved token type is 0x11f (end-of-file or special)
        if (*(int *)(this + 0x14) == 0x11f) {
            // Get next token from peek buffer
            int nextToken = getNextToken(this + 0x10);
            *(int *)(this + 0xc) = nextToken;
            processToken();
        } else {
            // Shift token stack: current = saved, saved = next, next = 0x11f
            *(int *)(this + 0xc) = *(int *)(this + 0x14);
            *(int *)(this + 0x10) = *(int *)(this + 0x18);
            *(int *)(this + 0x14) = 0x11f;
            processToken();
        }
    } else {
        // If not 0x104, just free the node once
        freeTokenNode(tokenNode);
    }
    
    // Update node's previous pointer again
    *(int *)(tokenNode + 0x1c) = *(int *)(tokenNode + 0x18);
    freeTokenNode(tokenNode);
    
    // Handle token type 0x106 (expected token, e.g., semicolon or closing brace)
    if (*(int *)(this + 0xc) == 0x106) {
        // Save previous token
        *(int *)(this + 8) = *(int *)(this + 4);
        if (*(int *)(this + 0x14) != 0x11f) {
            // Shift token stack
            *(int *)(this + 0xc) = *(int *)(this + 0x14);
            *(int *)(this + 0x10) = *(int *)(this + 0x18);
            *(int *)(this + 0x14) = 0x11f;
            return;
        }
        int nextToken = getNextToken(this + 0x10);
        *(int *)(this + 0xc) = nextToken;
        return;
    }
    
    // Error: expected token 0x106 but found something else
    if (lineNumber == *(int *)(this + 4)) {
        // Format error message: "`%s' expected"
        int errorMsg = formatString("`%s' expected", PTR_DAT_00e2a8d4);
        lineNumber = printError(errorMsg);
    }
    // Format detailed error with line number
    int errorMsg = formatString("`%s' expected (to close `%s' at line %d)",
                                PTR_DAT_00e2a8d4, PTR_DAT_00e2a8e4, lineNumber);
    printError(errorMsg);
    // Trigger debug breakpoint
    void (*breakpoint)() = (void (*)())swi(3);
    breakpoint();
}