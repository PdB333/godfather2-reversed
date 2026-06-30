// FUNC_NAME: LuaParser::compileForLoop
void __thiscall LuaParser::compileForLoop(int param_2) {
    int* codeGen = *(int**)(this + 0x1C); // this->codeGenerator (offset +0x1C? Actually unaff_EDI[7])
    int savedIndex = codeGen[0x9];          // backup current instruction index
    consumeToken(nullptr, 0);               // consume initial token (likely 'for')
    int forLimitToken = matchToken(this->lexer, "(for limit)", 0xB, 1); // get limit expression token
    consumeToken(forLimitToken);            // consume limit token
    int forStepToken = matchToken(this->lexer, "(for step)", 0xA, 2); // get step expression token
    consumeToken(forStepToken);             // consume step token
    
    if (this->currentToken == '=') { // expecting '=' after for init
        int stepEndMarker = 0x11F;    // marker for end of step expression
        this->varValue = this->varName; // copy variable name to value? (unaff_EDI[2] = unaff_EDI[1])
        if (this->limitToken == stepEndMarker) {
            this->currentToken = evaluateExpression(this + 4); // parse limit expression
        } else {
            this->currentToken = this->limitToken;
            this->limitExpr = this->stepExpr; // shift step to limit? (unaff_EDI[4] = unaff_EDI[6])
            this->limitToken = stepEndMarker;
        }
        advanceToken();
        emitForLoopNext(); // generate next step
        if (this->currentToken == ',') { // comma separates limit from step
            this->varValue = this->varName;
            if (this->limitToken == stepEndMarker) {
                // goto label inside loop (the loop body)
                goto loopBody;
            }
            // else parse step expression
            do {
                loopBody:
                    this->currentToken = evaluateExpression(this + 4); // this is the step?
                } else {
                    this->currentToken = this->limitToken;
                    this->limitExpr = this->stepExpr;
                    this->limitToken = stepEndMarker;
                }
                advanceToken();
                emitForLoopNext();
                // Check for comma again
                if (this->currentToken == ',') {
                    this->varValue = this->varName;
                    if (this->limitToken == stepEndMarker) {
                        this->currentToken = evaluateExpression(this + 4);
                    } else {
                        int tmp = this->limitToken;
                        this->limitExpr = this->stepExpr;
                        this->limitToken = stepEndMarker;
                        this->currentToken = tmp;
                    }
                    advanceToken();
                    emitForLoopNext();
                } else {
                    // no comma: prepare for loop body
                    int tmp = 3;
                    int dataSource = DAT_00e2b1a4; // some global data
                    uint encoded = encodeInstruction(codeGen, &tmp);
                    uint instruction = ( (codeGen[9] << 0x12 | encoded) << 6 ) | 1;
                    emitInstruction(instruction, *(undefined4*)(codeGen[3] + 8));
                    int nextIndex = codeGen[9] + 1;
                    if (nextIndex <= (uint)(*(byte*)(*codeGen + 0x47))) {
                        codeGen[9] = nextIndex;
                    } else if (nextIndex < 0xFA) {
                        *(char*)(*codeGen + 0x47) = (char)nextIndex;
                        codeGen[9] = nextIndex;
                    } else {
                        const char* errorMsg = "function or expression too complex";
                        codeGen = (int*)codeGen[3]; // switch to error context
                        reportError(errorMsg);
                    }
                }
            } while (true);
        }
    } else {
        // expected '=' or ','? Actually error: expected '='
        const char* expected = formatErrorMessage(&DAT_00e4242c, 0x2C); // ',' maybe?
        const char* errorMsg = formatErrorMessage("`%s\' expected", expected);
        codeGen = this; // unaff_EDI
        reportError(errorMsg);
    }
    
    // Common exit path for normal flow
    {
        int inst = (savedIndex * 0x40 - 0x3f) | (savedIndex * 0x8000 - 0x17fff) | (savedIndex * 0x1000000 + 0xfd000001) | 0xD;
        emitInstruction(inst, *(undefined4*)(codeGen[3] + 8));
        codeGen[8] = -1; // some flag
        uint data = emitInstruction(0x7FFF94, *(undefined4*)(codeGen[3] + 8));
        finalizeCodeBlock(codeGen);
        callForLoopRuntime(savedIndex, param_2, 3, 1); // execute for loop
        return;
    }
}