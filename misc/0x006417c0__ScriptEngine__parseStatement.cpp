// FUNC_NAME: ScriptEngine::parseStatement
// Address: 0x006417c0
// Role: Parses a statement in the EARS scripting language, handling token sequences and recursion depth.
// The parser context structure fields:
// +0x04: savedTokenValue? (used for semicolon handling)
// +0x08: prevTokenValue? (set from +0x04)
// +0x0C: current token type (e.g., 0x3b = ';', 0x104-0x11f = statement terminators)
// +0x10, +0x14, +0x18: expression stack or temporary state
// +0x1C: pointer to some scanner/line info (with +0x34 -> +0x24 copy)
// +0x30: recursion depth counter
// +0x34, +0x24 within scanner: line number or similar

void ScriptEngine::parseStatement(ParserContext* ctx)
{
    int tokenResult;
    int newToken;

    // Check recursion depth to avoid stack overflow
    ctx->depth += 1;
    if (ctx->depth > 200) {
        errorReport("too many syntax levels"); // FUN_00638b80
    }

    do {
        // If current token is a statement terminator, break loop
        switch (ctx->currentToken) {
        case 0x104:
        case 0x105:
        case 0x106:
        case 0x114:
        case 0x11f:
            goto exitParse;
        }

        // Read next token from input
        tokenResult = readToken(); // FUN_00641680

        // Handle semicolon token: acts as a statement separator
        if (ctx->currentToken == 0x3b) {
            ctx->prevTokenValue = ctx->savedTokenValue; // +0x08 = +0x04
            if (ctx->stackToken == 0x11f) { // +0x14 == 0x11f (special marker)
                newToken = parseExpression(ctx->stack); // FUN_00639c70 on +0x10
                ctx->currentToken = newToken;
            }
            else {
                // Pop the expression stack: shift values
                ctx->currentToken = ctx->stackToken;       // +0x0C = +0x14
                ctx->stackTokenValue = ctx->stackValue;     // +0x10 = +0x18
                ctx->stackToken = 0x11f;                    // +0x14 = 0x11f (reset stack marker)
            }
        }

        // Synchronize scanner line info (likely copy from scanner line end to line start)
        *(int*)(*(int*)(ctx + 0x1c) + 0x24) = *(int*)(*(int*)(ctx + 0x1c) + 0x34);
    } while (tokenResult == 0); // Continue while token reading succeeds (returns 0)

exitParse:
    ctx->depth -= 1;
    return;
}