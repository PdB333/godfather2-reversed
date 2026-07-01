// FUNC_NAME: ExpressionParser::parseExpression
// Address: 0x0077aee0
// Recursive-descent parser building an expression tree from a lexer state.
// LexerState: +0x00 = char* current pointer, +0x04 = int remaining count.
// Returns allocated expression node (size 8, 0xc, or 0x14 depending on type).
// VTable pointers:
//   0x00d684bc -> char literal node (size 8, vtable+0, data byte at +4)
//   0x00d684a8 -> number literal node (size 8, vtable+0, value at +4)
//   0x00d68494 -> binary operator node (size 20, vtable+0, op at +4, left at +8, right at +12, ??? at +16)
// Also creates identifier nodes (size 12) via helper that builds a string.

ExpressionNode* ExpressionParser::parseExpression(LexerState* state)
{
    char firstChar;
    int operatorType;
    bool flagNegate;
    ExpressionNode* resultNode;
    ExpressionNode* rightNode;
    uint uVar3;
    ExpressionNode* leftNode;
    int intVal;
    int subLen;
    bool flagContinue;
    char charLiteral;
    int numLiteral;
    char* tokenStr;
    int tokenLen;
    int typeCode;
    int somePtr;
    LexerState subState;
    LexerState localState;

    // If no remaining characters, allocate a char literal with value 1? (maybe default true)
    if (state->remaining == 0) {
        resultNode = (ExpressionNode*)operatorNew(8);
        if (resultNode != nullptr) {
            resultNode->vtable = &kCharLiteralVTable; // PTR_LAB_00d684bc
            resultNode->data.charLiteral = 1;         // char value 1 (maybe 'true'?)
        }
        return resultNode;
    }

    // Check for negation '!'
    flagNegate = (state->currentPtr[0] == '!');
    if (flagNegate) {
        advanceToken(state, 1);      // consume '!'
        advanceToken(state, 0);      // skip whitespace? actually just a call
    }

    // Handle parentheses: '(' subexpression ')'
    if (state->currentPtr[0] == '(') {
        // Find matching ')'
        uVar3 = findMatchingCloseParen(state);  // FUN_0077ab40
        if (state->remaining <= uVar3) {
            // Error: unmatched parenthesis
            advanceToken(state, 1);  // skip '('?
            resultNode = parseExpression(state);
            goto done;
        }
        // Move past '('
        advanceToken(state, 1);
        // Move past the whole parenthesized content? Actually advances twice?
        advanceToken(state, 1);
        // Now state points after '('? No, it's a bit odd. Let's interpret as:
        // We skip the '(' and then the subexpression length. Possibly the lexer stores lengths.
        // We'll keep as-is but rename functions.
        skipToken(state, uVar3);     // FUN_004d45e0? Actually it advances by (uVar3 - state->remaining) something.
        // Then skip the closing ')'
        advanceToken(state, 1);      // consume ')'

        // Recursively parse the enclosed expression (with negation flag still active)
        localState = *state;         // copy? Actually uses local variables at local_20, etc.
        // But the code saves state into local_20 and local_30; we'll simplify.
        // After parsing the subexpression, we may have an operator.
        resultNode = parseExpression(&localState);
        if (flagNegate) {
            // Wrap in a negation node: op=0xb (maybe logical not)
            resultNode = createUnaryNode(resultNode, 0xb);  // FUN_009c8e50 + setup
            flagNegate = false;
        }
        // Now parse the operator (if any) using the original state? The code reads operator from local_30.
        operatorType = readOperatorType(state);  // FUN_0077ae30
        if (operatorType != 0xc) {   // 0xc may be end-of-expression?
            rightNode = parseExpression(state);
            resultNode = createBinaryNode(operatorType, resultNode, rightNode);
        }
    }
    else {
        // Not a '(': try to parse a token (string, number, char literal)
        memset(&localState, 0, sizeof(LexerState));
        memset(&subState, 0, sizeof(LexerState));

        // Try to read a token (identifier or number) into localState and subState
        if (getToken(state, &localState, &subState)) {  // FUN_004d5210
            // Successfully got a token; parse it recursively (should be a leaf)
            resultNode = parseExpression(&localState);
            if (flagNegate) {
                resultNode = createUnaryNode(resultNode, 0xb);
                flagNegate = false;
            }
            operatorType = readOperatorType(&subState);
            if (operatorType != 0xc) {
                rightNode = parseExpression(&subState);
                resultNode = createBinaryNode(operatorType, resultNode, rightNode);
            }
        }
        else {
            // Try char literal (single-quoted)
            if (parseCharLiteral(state, &charLiteral)) {   // FUN_0077ab80
                resultNode = (ExpressionNode*)operatorNew(8);
                if (resultNode != nullptr) {
                    resultNode->vtable = &kCharLiteralVTable;
                    resultNode->data.charLiteral = charLiteral;
                }
            }
            // Try number literal
            else if (parseNumberLiteral(state, &numLiteral)) {  // FUN_0077abd0
                resultNode = (ExpressionNode*)operatorNew(8);
                if (resultNode != nullptr) {
                    resultNode->vtable = &kNumberLiteralVTable;  // PTR_LAB_00d684a8
                    resultNode->data.numLiteral = numLiteral;
                }
            }
            // Otherwise, it's an identifier (variable)
            else {
                tokenStr = parseIdentifier(state);               // FUN_0077ac20
                resultNode = createIdentifierNode(tokenStr);    // FUN_0077a910 + alloc size 12
            }
        }
    }

done:
    // Clean up temporary states if they were allocated
    if (subState.basePtr != 0) {
        subState.vtable->destroy(&subState);
    }
    if (localState.basePtr != 0) {
        localState.vtable->destroy(&localState);
    }

    // If negation flag is still set (e.g., from a parenthesized expression without wrapping)
    if (flagNegate) {
        resultNode = createUnaryNode(resultNode, 0xb);
    }
    return resultNode;
}
```