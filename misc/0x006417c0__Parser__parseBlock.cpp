// FUNC_NAME: Parser::parseBlock
// Function address: 0x006417c0
// Role: Core syntax parser for script blocks. Processes tokens until a block-ending token is encountered,
// tracking nesting depth to prevent excessive recursion.

void __thiscall Parser::parseBlock(ParserContext* ctx)
{
    int tokenResult;
    uint newTokenType;

    // Increment syntax depth
    ctx->syntaxDepth = ctx->syntaxDepth + 1; // +0x30
    if (200 < ctx->syntaxDepth) {
        Parser::reportError("too many syntax levels"); // FUN_00638b80
    }

    do {
        switch (ctx->currentTokenType) { // +0x0c
        case TOKEN_TYPE_END_BLOCK_1:
        case TOKEN_TYPE_END_BLOCK_2:
        case TOKEN_TYPE_END_BLOCK_3:
        case TOKEN_TYPE_END_BLOCK_4:
        case TOKEN_TYPE_END_BLOCK_5:
            // Block-ending tokens, exit immediately
            goto EXIT;
        }

        // Advance to next token; returns 0 while more tokens available
        tokenResult = Parser::getNextToken(); // FUN_00641680
        if (ctx->currentTokenType == TOKEN_SEMICOLON) { // 0x3b
            // Save previous token as current
            ctx->savedToken = ctx->prevToken; // +0x08 = +0x04
            if (ctx->lookaheadTokenType == TOKEN_TYPE_END_BLOCK_5) { // +0x14, 0x11f
                // Resolve token type from lookahead value
                newTokenType = Parser::resolveTokenType(ctx + 0x10); // FUN_00639c70
                ctx->currentTokenType = newTokenType;
            } else {
                // Shift lookahead into current, then reset lookahead
                ctx->currentTokenType = ctx->lookaheadTokenType;
                ctx->lookaheadTokenValue = ctx->lookaheadValue; // +0x10 = +0x18
                ctx->lookaheadTokenType = TOKEN_TYPE_END_BLOCK_5; // 0x11f
            }
        }
        // Update a field in the lexer context (likely statement count?)
        *(int*)(*(int*)(ctx + 0x1c) + 0x24) = *(int*)(*(int*)(ctx + 0x1c) + 0x34);
    } while (tokenResult == 0);

EXIT:
    // Decrement syntax depth
    ctx->syntaxDepth = ctx->syntaxDepth - 1;
    return;
}