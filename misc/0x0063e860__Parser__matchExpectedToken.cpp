// FUNC_NAME: Parser::matchExpectedToken
void Parser::matchExpectedToken(int* tokenStream /* likely passed in EAX */) {
    // +4 = current input position, +8 = previous position
    this->previousPos = this->currentPos; // *(param_1+8) = *(param_1+4)

    if (this->nextTokenType == 0x11f) { // 287 = end-of-file sentinel
        this->currentTokenType = getNextToken(this->tokenValue); // FUN_00639c70(param_1+0x10) -> token value
        this->currentTokenValue = ... ; // returned from getNextToken
    } else {
        this->currentTokenType = this->nextTokenType;         // +0xc = +0x14
        this->currentTokenValue = this->nextTokenValue;       // +0x10 = +0x18
        this->nextTokenType = 0x11f;                         // mark as consumed
    }

    advanceParser(); // FUN_0063fad0(param_1)

    int* statePtr = this->state; // +0x1c

    if (tokenStream[3] == tokenStream[4]) {
        fetchNextToken(); // FUN_00642b00()
        goto checkExpected;
    }

    fetchNextToken(); // FUN_00642b00()
    if (tokenStream[0] == 0xb) { // 11 = some token type
        if (tokenStream[3] == tokenStream[4]) goto checkExpected;
        if (statePtr[0xD] <= tokenStream[1]) { // state+0x34
            matchString(tokenStream[1]); // FUN_00642d90
            goto checkExpected;
        }
    }

    skipWhitespace(); // FUN_00642ec0()

checkExpected:
    if (this->currentTokenType != 0x5d) { // 93 = ']'
        char* fmt = "`%s' expected";
        char* expectedName = formatString(DAT_00e4242c, 0x5d); // FUN_00636c00
        reportError(formatString(fmt, expectedName)); // FUN_00638b80
        __debugbreak(); // swi(3)
        return;
    }

    // Re-apply the initial shift to ensure consistency
    this->previousPos = this->currentPos;
    if (this->nextTokenType != 0x11f) {
        this->currentTokenType = this->nextTokenType;
        this->currentTokenValue = this->nextTokenValue;
        this->nextTokenType = 0x11f;
    } else {
        this->currentTokenValue = getNextToken(this->tokenValue);
    }
}