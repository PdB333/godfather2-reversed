// FUNC_NAME: ScriptCompiler::parseFunctionCall
void ScriptCompiler::parseFunctionCall(void* parserContext, int* instructionData) {
    // parserContext: +0x00 unknown, +0x04 currentRegisterIndex, +0x08 expectedRegisterIndex, +0x0C currentToken, +0x1C codeBuffer
    // instructionData: array[0]=res, [1]=argReg, [2]=? , [3]=?, [4]=?
    
    int currentRegister = *(int*)((char*)parserContext + 0x04);
    int expectedRegister = *(int*)((char*)parserContext + 0x08);
    int currentToken = *(int*)((char*)parserContext + 0x0C);
    int* codeBuffer = *(int**)((char*)parserContext + 0x1C);  // points to code generation context
    
    int prevArgReg;  // from instructionData[1]
    int argOffset;   // local_14, gets set by parseExpression or default
    int stackTemp;   // iStack_10, unused
    
    if (currentToken == 0x28) {  // '('
        if (currentRegister != expectedRegister) {
            errorReport("ambiguous syntax (function call x new statement)");
        }
        readNextToken();
        if (*(int*)((char*)parserContext + 0x0C) == 0x29) {  // ')'
            argOffset = 0;
        } else {
            parseExpression(parserContext, &argOffset, &stackTemp);
            if (argOffset == 0x0C) {
                // clear bits 6-13 (0x3F << 6) in a uint at codeBuffer->someArray[stackTemp]
                unsigned int* ptr = (unsigned int*)(*(int*)(*(int*)codeBuffer + 0x0C) + stackTemp * 4);
                *ptr &= 0xFFFF803F;
            }
        }
        emitInstruction(currentRegister);
    } else if (currentToken == 0x7B) {  // '{'
        parseBlock(parserContext);
    } else if (currentToken == 0x11E) {
        parseStatementSemicolon();  // or parseStatementEnd
        readNextToken();
    } else {
        errorReport("function arguments expected");
    }
    
    prevArgReg = instructionData[1];
    if (argOffset == 0x0C) {
        // use -1 as special marker
        int argCount = -1;
    } else {
        if (argOffset != 0) {
            emitPopStack();  // clean up stack?
        }
        // compute argCount as (codeBuffer[9] - prevArgReg - 1)
        int argCount = (codeBuffer[9] - prevArgReg) - 1;
    }
    
    // Build a VM instruction: opcode 0x99 with encoded arguments
    int encodedInstruction = buildInstruction(
        (argCount + 1) * 0x8000 | prevArgReg << 0x18 | 0x99,
        *(int*)(codeBuffer[3] + 8)  // some constant table?
    );
    instructionData[1] = encodedInstruction;
    instructionData[3] = -1;
    instructionData[4] = -1;
    instructionData[0] = 0x0C;  // marks some type
    
    // Backpatch: write currentRegister into code buffer at codeBuffer[6] offset
    int* codeArray = *(int**)(*(int*)codeBuffer + 0x14);
    int writePos = (codeBuffer[6] * 4) - 4;
    codeArray[writePos / 4] = currentRegister;
    
    // Update codeBuffer[9] to prevArgReg + 1
    codeBuffer[9] = prevArgReg + 1;
}