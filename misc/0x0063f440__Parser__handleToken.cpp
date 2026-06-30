// FUNC_NAME: Parser::handleToken
// Address: 0x0063f440
// This function processes a token from the parser's state machine.
// It is a member function (this in ECX). The 'this' pointer has fields representing the current token and state.
// Constants: 0x28 = 40 (likely TOKEN_TYPE_IDENTIFIER), 0x116 = 278 (TOKEN_TYPE_EXPRESSION), 0x11f = 287 (TOKEN_TYPE_UNKNOWN)

void __thiscall Parser::handleToken(int context)
{
    // 'this' is implicit via ECX. We'll use a pointer to a hypothetical struct.
    // offsets:
    // +0x04: tokenValue (undefined4)
    // +0x08: savedTokenValue (undefined4)
    // +0x0C: currentTokenType (int)
    // +0x10: currentTokenData (undefined4) - maybe a pointer or value
    // +0x14: nextTokenType (int)
    // +0x18: nextTokenData (undefined4)
    // +0x1C: something else (undefined4) - argument to handleExpression

    int tokenType = *(int *)(this + 0x0C);  // current token type

    if (tokenType != 0x28) {  // TOKEN_TYPE_IDENTIFIER
        if (tokenType != 0x116) {  // TOKEN_TYPE_EXPRESSION
            errorPrint("unexpected symbol");  // FUN_00638b80
        }

        // Handle expression token type (0x116)
        int expressionData = getNextToken();  // FUN_0063dd40
        handleExpression(*(int *)(this + 0x1C), expressionData, context, 1);  // FUN_0063e160
        return;
    }

    // Token type is 0x28 (identifier)
    int tokenVal = *(int *)(this + 0x04);
    *(int *)(this + 0x08) = tokenVal;  // save token value

    int nextType = *(int *)(this + 0x14);
    if (nextType == 0x11f) {  // Some special state
        int resolvedType = resolveTypeFromData(this + 0x10);  // FUN_00639c70
        *(int *)(this + 0x0C) = resolvedType;
    } else {
        // Shift data: move next to current, set next to 0x11f
        *(int *)(this + 0x0C) = *(int *)(this + 0x14);
        *(int *)(this + 0x10) = *(int *)(this + 0x18);
        *(int *)(this + 0x14) = 0x11f;
    }

    pushState();     // FUN_0063fad0
    consumeToken(tokenVal);  // FUN_0063dc80
    evaluate();       // FUN_00642b00
}