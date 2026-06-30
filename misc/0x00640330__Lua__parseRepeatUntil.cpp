//FUNC_NAME: Lua::parseRepeatUntil
void Lua::parseRepeatUntil(int lineNumber)
{
    // this is in EAX
    // Offsets:
    // +0x04: currentTokenType (int)
    // +0x08: savedTokenType (int)
    // +0x0C: tokenType (int)
    // +0x10: tokenValue (int)
    // +0x14: tokenString (char*)
    // +0x18: nextTokenType (int)
    // +0x1C: scopeStack (Scope*)

    // Scope structure offsets:
    // +0x14: tokenString (char*)
    // +0x18: nextTokenType (int)
    // +0x1C: currentTokenType (int)
    // +0x34: someValue (int)

    Scope* scope = *(Scope**)(this + 0x1C);
    int savedNextToken = *(int*)(scope + 0x18);
    scope->currentTokenType = savedNextToken;

    // Temporary token for the 'repeat' keyword
    int tempTokenType = 0xFFFFFFFF; // -1
    int tempTokenValue = 1;
    int tempSomeValue = *(int*)(scope + 0x34);
    int tempUnk = 0;
    char* tempTokenString = *(char**)(scope + 0x14);
    scope->tokenString = &tempTokenString; // point to local

    // Save current token type
    *(int*)(this + 0x08) = *(int*)(this + 0x04);

    // Check if current token is 'repeat' (0x11F)
    if (*(int*)(this + 0x14) == 0x11F) {
        int tokenType = FUN_00639c70(this + 0x10); // get token type from value
        *(int*)(this + 0x0C) = tokenType;
    } else {
        *(int*)(this + 0x0C) = *(int*)(this + 0x14);
        *(int*)(this + 0x10) = *(int*)(this + 0x18);
        *(int*)(this + 0x14) = 0x11F; // set to 'repeat'
    }

    // Now parse the body of the repeat loop
    Scope* bodyScope = *(Scope**)(this + 0x1C);
    // Another temporary token for the body
    int bodyTempTokenType = 0xFFFFFFFF;
    int bodyTempUnk = 0;
    int bodyTempSomeValue = *(int*)(bodyScope + 0x34);
    int bodyTempUnk2 = 0;
    char* bodyTempTokenString = *(char**)(bodyScope + 0x14);
    bodyScope->tokenString = &bodyTempTokenString;

    FUN_006417c0(); // parseStatement or parseBlock
    FUN_0063e400(); // advance token

    // Check if the next token is 'until' (0x114)
    if (*(int*)(this + 0x0C) == 0x114) {
        // Save current token type again
        *(int*)(this + 0x08) = *(int*)(this + 0x04);

        if (*(int*)(this + 0x14) == 0x11F) {
            int tokenType = FUN_00639c70(this + 0x10);
            *(int*)(this + 0x0C) = tokenType;
        } else {
            *(int*)(this + 0x0C) = *(int*)(this + 0x14);
            *(int*)(this + 0x10) = *(int*)(this + 0x18);
            *(int*)(this + 0x14) = 0x11F;
        }

        FUN_0063fad0(); // parseExpression (the condition)
        if (*(int*)(this + 0x1C) == 1) { // some flag?
            *(int*)(this + 0x1C) = 3;
        }
        FUN_00643310(); // parseStatement or end of block

        // Pop the body scope
        Scope* bodyScope2 = *(Scope**)(this + 0x1C);
        bodyScope2->currentTokenType = bodyScope2->nextTokenType;
        FUN_00642880(bodyScope2); // free/pop scope

        if (savedNextToken == *(int*)(scope + 0x18)) {
            scope->currentTokenType = scope->nextTokenType;
            FUN_00642880(scope); // pop the repeat scope
            FUN_0063e400(); // advance token
            return;
        }
    } else {
        // Error: expected 'until'
        if (lineNumber == *(int*)(this + 0x04)) {
            int errorMsg = FUN_00636c00("`%s' expected", PTR_s_until_00e2a90c);
            lineNumber = FUN_00638b80(errorMsg);
        }
        int errorMsg = FUN_00636c00("`%s' expected (to close `%s' at line %d)",
                                    PTR_s_until_00e2a90c,
                                    PTR_s_repeat_00e2a8fc,
                                    lineNumber);
        FUN_00638b80(errorMsg);
    }

    // Cleanup: free tokens and advance
    FUN_006426a0(scope, savedNextToken, 0xFF, savedNextToken, 0xFF, savedNextToken);
    FUN_0063e400();
    return;
}