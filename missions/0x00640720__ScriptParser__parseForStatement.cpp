// FUNC_NAME: ScriptParser::parseForStatement
void __thiscall ScriptParser::parseForStatement(int param_1, int param_2)
{
    int tokenType;
    int tokenValue;
    int expectedToken;
    int codeOffset;
    int *codeGen;
    char *errorMsg;

    codeGen = (int *)this[7]; // +0x1C? code generator pointer
    codeOffset = codeGen[9];  // current code offset

    // Emit "for" keyword and loop variable setup
    emitToken(param_1, 0);
    tokenValue = lookupString(this[8], "(for limit)", 0xB, 1);
    emitToken(tokenValue);
    tokenValue = lookupString(this[8], "(for step)", 10, 2);
    emitToken(tokenValue);

    if (this[3] == 0x3D) // '=' token
    {
        expectedToken = 0x11F; // some token type (maybe 'TO')
        this[2] = this[1]; // save current token
        if (this[5] == 0x11F)
        {
            tokenType = getNextToken(this + 4);
            this[3] = tokenType;
        }
        else
        {
            this[3] = this[5];
            this[4] = this[6];
            this[5] = 0x11F;
        }
        advance();
        parseExpression();

        if (this[3] == 0x2C) // ',' token
        {
            this[2] = this[1];
            if (this[5] == 0x11F)
                goto LAB_00640870;
            this[3] = this[5];
            this[4] = this[6];
            this[5] = 0x11F;
            do
            {
                advance();
                parseExpression();
                if (this[3] == 0x2C)
                {
                    this[2] = this[1];
                    if (this[5] == expectedToken)
                    {
                        tokenType = getNextToken(this + 4);
                    }
                    else
                    {
                        tokenType = this[5];
                        this[4] = this[6];
                        this[5] = expectedToken;
                    }
                    this[3] = tokenType;
                    advance();
                    parseExpression();
LAB_00640925:
                    // Emit loop body bytecode
                    emitBytecode((codeGen[9] * 0x40 - 0x3F) | (codeGen[9] * 0x8000 - 0x17FFF) |
                                 (codeGen[9] * 0x1000000 + 0xFD000001) | 0xD,
                                 *(undefined4 *)(codeGen[3] + 8));
                    codeGen[8] = -1; // reset jump offset
                    emitBytecode(0x7FFF94, *(undefined4 *)(codeGen[3] + 8));
                    finalizeCodeGen(codeGen);
                    executeLoop(codeOffset, param_2, 3, 1);
                    return;
                }
                // Evaluate loop condition
                tokenType = 3;
                tokenValue = DAT_00e2b1a4;
                int condition = evaluateCondition(codeGen, &tokenType);
                emitBytecode(((codeGen[9] << 0x12) | condition) << 6 | 1,
                             *(undefined4 *)(codeGen[3] + 8));
                int nextOffset = codeGen[9] + 1;
                if (nextOffset <= (int)(uint)*(byte *)(*codeGen + 0x47))
                {
LAB_00640921:
                    codeGen[9] = codeGen[9] + 1;
                    goto LAB_00640925;
                }
                if (nextOffset < 0xFA)
                {
                    *(char *)(*codeGen + 0x47) = (char)nextOffset;
                    goto LAB_00640921;
                }
                errorMsg = "function or expression too complex";
                codeGen = (int *)codeGen[3];
LAB_0064086B:
                reportError(errorMsg);
LAB_00640870:
                tokenType = getNextToken(this + 4);
                this[3] = tokenType;
            } while (true);
        }
        expectedToken = 0x2C;
    }
    else
    {
        expectedToken = 0x3D;
    }
    // Error: expected token
    tokenValue = formatString(&DAT_00e4242c, expectedToken);
    errorMsg = (char *)formatString("`%s' expected", tokenValue);
    codeGen = this; // use this as error context
    goto LAB_0064086B;
}