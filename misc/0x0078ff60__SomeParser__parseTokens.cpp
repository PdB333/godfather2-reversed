// FUNC_NAME: SomeParser::parseTokens
void __thiscall SomeParser::parseTokens(uint source) {
    char isDone;
    int tokenType;

    FUN_0043aff0(source, 0x369ac561);
    isDone = FUN_0043b120();
    while (isDone == '\0') {
        FUN_0043b210();
        tokenType = FUN_0043ab70();
        if (tokenType == 9) {
            int token = FUN_0043b210();
            *(uint *)(this + 0xd4) = *(uint *)(token + 8);
        } else if (tokenType == 0x11) {
            int token = FUN_0043b210();
            *(uint *)(this + 0xcc) = *(uint *)(token + 8);
        } else if (tokenType == 0x12) {
            int token = FUN_0043b210();
            *(uint *)(this + 0xc4) = *(uint *)(token + 8);
        }
        FUN_0043b1a0();
        isDone = FUN_0043b120();
    }
}