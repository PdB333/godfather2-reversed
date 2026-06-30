// FUNC_NAME: ScriptParser::parseCallExpression
void ScriptParser::parseCallExpression(ScriptParser *this, uint32_t *result)
{
    uint32_t *bytecodeStack;
    int32_t tokenType;
    int32_t *context;
    int32_t currentTokenCount;
    int32_t argCount;
    int32_t uninitialized;
    uint32_t encodedInstruction;

    // +0x0c: current token type
    tokenType = *(int32_t *)(this + 0xc);
    // +0x1c: pointer to some context (stack/state)
    context = *(int32_t **)(this + 0x1c);
    // +0x04: current token index / count
    currentTokenCount = *(int32_t *)(this + 4);

    if (tokenType == 0x28) { // '(' - function call or new?
        // Check if ambiguous: new vs function call
        if (currentTokenCount != *(int32_t *)(this + 8)) {
            reportError("ambiguous syntax (function call x new statement)");
        }
        parseExpression(); // parse the expression inside parens (for new?)
        if (*(int32_t *)(this + 0xc) == 0x29) { // ')'
            uninitialized = 0;
        } else {
            parseFunctionArguments(this); // parse comma-separated args
            if (uninitialized == 0xc) { // some flag check
                bytecodeStack = (uint32_t *)(*(int32_t *)(*context + 0xc) + uninitializedStackVar * 4);
                *bytecodeStack = *bytecodeStack & 0xffff803f;
            }
        }
        popStack(currentTokenCount); // restore token count
    } else if (tokenType == 0x7b) { // '{' - block?
        parseBlock(this);
    } else {
        if (tokenType != 0x11e) { // 0x11e likely denotes something else (e.g., statement start)
            reportError("function arguments expected");
        }
        parseParenExpression(); // parse something with parens
        parseExpression();
    }

    int32_t baseArgIndex = result[1]; // result[1] is arg index base?
    if (uninitialized == 0xc) {
        argCount = -1;
    } else {
        if (uninitialized != 0) {
            emitSomeOpcode(); // maybe store arg count?
        }
        argCount = (context[9] - baseArgIndex) - 1;
    }

    // Encode instruction: opcode 0x99, shift 0x8000, combine with arg index and count
    encodedInstruction = encodeInstruction((argCount + 1) * 0x8000 | baseArgIndex << 0x18 | 0x99,
                                           *(uint32_t *)(context[3] + 8));
    result[1] = encodedInstruction;
    result[3] = 0xffffffff;
    result[4] = 0xffffffff;
    result[0] = 0xc; // result type constant

    // Store current token count into context stack
    *(int32_t *)(*(int32_t *)(*context + 0x14) + -4 + context[6] * 4) = currentTokenCount;
    context[9] = baseArgIndex + 1; // advance argument index
}