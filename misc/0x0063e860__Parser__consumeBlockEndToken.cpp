// FUNC_NAME: Parser::consumeBlockEndToken
void __thiscall Parser::consumeBlockEndToken(Parser* this)
{
    int inputValue;
    int tokenType;
    int currentToken;
    int nextToken;
    int tokenValue;

    // Save previous token
    this->savedToken = this->tokenValue;

    // Handle lookahead token
    if (this->lookahead == 0x11f) // EOF_TOKEN
    {
        // Fetch next token from input stream
        currentToken = fetchNextToken(&this->currentToken);
        this->tokenType = currentToken;
    }
    else
    {
        // Shift lookahead tokens
        this->tokenType = this->lookahead;
        this->currentToken = this->savedLookahead;
        this->lookahead = 0x11f; // clear lookahead to indicate EOF
    }

    // Process the current token
    advanceInputStream(this);

    // Check if we've reached a loop end (current == next)
    if (this->currentToken == this->nextToken)
    {
        handleLoopEnd();
        goto expectedBracketCheck;
    }
    handleLoopEnd();

    // If token type is a specific loop keyword (0x0b = WHILE)
    if (this->tokenType == 0xb)
    {
        if (this->currentToken == this->nextToken)
            goto expectedBracketCheck;

        // Check if we should continue looping based on input value
        inputValue = this->input->field_0x34; // some loop condition
        if (inputValue <= this->tokenValue)
        {
            continueLoop(this->tokenValue);
            goto expectedBracketCheck;
        }
    }
    handleLoopIteration();

expectedBracketCheck:
    // Expect a closing bracket token (0x5d = ']')
    if (this->tokenType != 0x5d)
    {
        // Format error message: "`%s' expected"
        const char* expectedTokenStr = tokenToString(0x5d);
        const char* formatStr = getErrorFormatString(); // e.g., "`%s' expected"
        char* errorMsg = formatString(formatStr, expectedTokenStr);
        reportError(errorMsg);
        // Trigger debug breakpoint
        __debugbreak();
        return;
    }

    // Restore token value after successful bracket consumption
    this->savedToken = this->tokenValue;

    // Again handle lookahead (likely to prepare for next token)
    if (this->lookahead != 0x11f) // EOF_TOKEN
    {
        this->tokenType = this->lookahead;
        this->currentToken = this->savedLookahead;
        this->lookahead = 0x11f;
    }
    else
    {
        currentToken = fetchNextToken(&this->currentToken);
        this->tokenType = currentToken;
    }
}