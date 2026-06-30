// FUNC_NAME: ScriptParser::parseForAssignment
void ScriptParser::parseForAssignment(int lineNumber)
{
    // this = in_EAX
    int lexerState = *(int *)(this + 0x1c);  // +0x1c: pointer to LexerState
    Token tokenStack[5];  // local_14, local_10, local_c, local_8, local_4
    tokenStack[0] = 0;                           // local_4 = 0 (maybe token type)
    tokenStack[1] = 0xffffffff;                 // local_10 = -1 (maybe token value)
    tokenStack[2] = *(int *)(lexerState + 0x34); // local_c: line number?
    tokenStack[3] = 0;                           // local_8 = 0
    tokenStack[4] = *(int *)(lexerState + 0x14); // local_14: token type?
    *(int **)(lexerState + 0x14) = &tokenStack[4]; // save stack pointer for rollback

    // Save current token as previous
    *(int *)(this + 0x8) = *(int *)(this + 0x4); // +0x8: previousTokenType, +0x4: currentTokenType

    if (*(int *)(this + 0x14) == 0x11f) {        // +0x14: savedState marker (0x11f means empty)
        *(int *)(this + 0xc) = getNextToken(this + 0x10); // call FUN_00639c70: get token from stream, store at +0xc
    } else {
        // Restore previously saved token state
        *(int *)(this + 0xc) = *(int *)(this + 0x14);
        *(int *)(this + 0x10) = *(int *)(this + 0x18);
        *(int *)(this + 0x14) = 0x11f;  // mark as consumed
    }

    int nextTokenType = getCurrentTokenType();   // FUN_0063dd40: returns token type
    int token = *(int *)(this + 0xc);           // token type we are processing

    if (token == 0x2c) {                         // ',' comma
        parseExpression(nextTokenType);           // FUN_006409b0: handle expression
    } else if (token != 0x3d) {                  // '='
        if (token == 0x10b) {                     // 'in' keyword
            parseExpression(nextTokenType);       // same handler
        } else {
            reportError("`=\' or `in\' expected"); // FUN_00638b80
        }
        parseAssignmentRHS(lineNumber);           // FUN_00640720: parse right-hand side of assignment
    } else {                                      // token == '='
        parseAssignmentRHS(lineNumber);           // FUN_00640720
    }

    // Now expect a closing token (e.g., 'do' or 'then')
    if (*(int *)(this + 0xc) != 0x106) {         // 0x106: expected closing token (maybe 'do')
        if (lineNumber == *(int *)(this + 0x4)) {
            reportFormattedError("`%s\' expected", stringPtr1); // FUN_00636c00
        } else {
            reportFormattedError("`%s\' expected (to close `%s\' at line %d)", 
                                stringPtr1, stringPtr2, lineNumber);
        }
        // Force debug break
        __debugbreak();  // swi(3) -> breakpoint
        return;
    }

    // Successfully parsed
    *(int *)(this + 0x8) = *(int *)(this + 0x4); // update previous token
    if (*(int *)(this + 0x14) != 0x11f) {
        // There is a saved token: restore it
        int savedToken = *(int *)(this + 0x14);
        *(int *)(this + 0x14) = 0x11f;
        *(int *)(this + 0xc) = savedToken;
        *(int *)(this + 0x10) = *(int *)(this + 0x18);
        pushBackToken();                // FUN_0063e400
    } else {
        // No saved token: get next token normally
        *(int *)(this + 0xc) = getNextToken(this + 0x10);
        pushBackToken();                // FUN_0063e400
    }
}