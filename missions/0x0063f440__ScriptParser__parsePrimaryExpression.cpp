// FUNC_NAME: ScriptParser::parsePrimaryExpression
void __thiscall ScriptParser::parsePrimaryExpression(ScriptParser *this, int param1) {
    int tokenType = *(int *)(this + 0xc); // +0xc current token type
    if (tokenType != 0x28) { // token: integer literal
        if (tokenType != 0x116) { // token: string literal
            FUN_00638b80("unexpected symbol");
        }
        // Handle string literal
        int strHandle = FUN_0063dd40();
        FUN_0063e160(*(int *)(this + 0x1c), strHandle, param1, 1); // +0x1c output storage
        return;
    }
    // Handle integer literal
    int literalValue = *(int *)(this + 0x4); // +0x4 token value
    *(int *)(this + 0x8) = literalValue; // +0x8 current result
    int nextTokenType = *(int *)(this + 0x14); // +0x14 next token type
    if (nextTokenType == 0x11f) { // 'next' sentinel?
        int newType = FUN_00639c70(this + 0x10); // +0x10 auxiliary token
        *(int *)(this + 0xc) = newType;
    } else {
        *(int *)(this + 0xc) = nextTokenType;
        *(int *)(this + 0x10) = *(int *)(this + 0x18); // +0x18 next token value
        *(int *)(this + 0x14) = 0x11f; // reset sentinel
    }
    FUN_0063fad0(); // advance parser
    FUN_0063dc80(literalValue);
    FUN_00642b00();
}