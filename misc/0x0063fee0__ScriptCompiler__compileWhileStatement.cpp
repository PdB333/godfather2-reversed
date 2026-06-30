// FUNC_NAME: ScriptCompiler::compileWhileStatement
void ScriptCompiler::compileWhileStatement(int errorLineNum) {
    // param_1 is this, param_2 is errorLineNum (source position for error messages)
    // Offsets for this:
    // +0x04: source position (int)
    // +0x08: expression source position (copy)
    // +0x0c: current token type (int)
    // +0x10: next token buffer? (used with token advance)
    // +0x14: current token value (int)
    // +0x18: line number (int)
    // +0x1c: pointer to bytecode context (int*)
    int* bcCtx = *(int**)(this + 0x1c); // bytecode generator context
    
    // Save the source position of the 'while' statement
    *(int*)(this + 8) = *(int*)(this + 4);
    
    // Check if the next token is an expression (0x11f = expression start marker)
    if (*(int*)(this + 0x14) == 0x11f) {
        // Advance to get the actual expression token
        int nextToken = nextToken(); // FUN_00639c70(this + 0x10)
        *(int*)(this + 0x0c) = nextToken;
    } else {
        // Otherwise keep current token and push a new expression state
        *(int*)(this + 0x0c) = *(int*)(this + 0x14);
        *(int*)(this + 0x10) = *(int*)(this + 0x18);
        *(int*)(this + 0x14) = 0x11f; // mark as expression start
    }
    
    // Reset the instruction counter marker
    bcCtx[8] = -1;
    
    // Emit debug info? (FUN_006438e0 with a string pointer and a context)
    emitDebugInfo(0x7fff94, *(int*)(bcCtx[3] + 8)); // FUN_006438e0
    
    // Save current instruction index as a mark
    saveState(bcCtx); // FUN_00642880(bcCtx)
    
    int condInstrStart = bcCtx[6]; // start of condition instructions
    bcCtx[7] = condInstrStart;
    
    // Parse the while condition expression
    int exprResult[?];
    parseExpression(this, exprResult, -1); // FUN_0063fad0(this, exprResult, 0xffffffff)
    
    // If the result type is 4 (boolean?), change to 2 (for conditional jump?)
    if (exprResult[0] == 4) {
        exprResult[0] = 2;
    }
    
    int condSrcPos = *(int*)(this + 4); // source position of condition
    
    // Emit bytecode for condition and get instruction count
    emitBoolCondition(); // FUN_006433b0? Not sure exact name
    
    // Restore original state (pop temporary saved state)
    restoreState(bcCtx); // FUN_00642880(bcCtx)
    
    int condInstrCount = bcCtx[6] - condInstrStart; // number of instructions for condition
    bcCtx[8] = -1;
    int instrCount = condInstrCount;
    int startInstr = condInstrStart;
    
    // Check if too complex (more than 100 instructions)
    if (100 < condInstrCount) {
        printError("`while' condition too complex"); // FUN_00638b80
        // Note: after error, extraout_ECX is used but not clearly; assume it modifies some state
        instrCount = ???; // not clear, but we ignore
        startInstr = this; // probably not used
    }
    
    // Copy the condition instructions to a local buffer (max 107)
    int savedInstr[107]; // local_1b0
    if (0 < instrCount) {
        int* src = (int*)(*(int*)(*bcCtx + 0x0c) + startInstr * 4); // bytecode buffer + offset
        int* dst = savedInstr;
        for (int i = 0; i < instrCount; i++) {
            *dst++ = *src++;
        }
    }
    bcCtx[6] = startInstr; // reset instruction pointer to before condition
    
    // Push a new scope for the while loop (contains continue and break labels)
    // Scope structure on stack: {prevScope, breakTarget, continueFlag, continueDepth?, 0, ???}
    // aiStack_1d8[0] = bcCtx[5] (previous scope), aiStack_1d8[1] = -1 (break target unused?), 
    // uStack_1c8 = 1 (continue flag? maybe 1 means continue not yet set), 
    // aiStack_1d8[2] = bcCtx[0xd] (scope depth), uStack_1cc = 0.
    int newScope[4] = {bcCtx[5], -1, 1, bcCtx[0xd]}; // simplified: we use only 4 fields for clarity
    bcCtx[5] = (int)newScope; // push scope onto the stack (note: it's a pointer to local array, which is dangerous; actual code uses stack allocation)
    
    // Actually the original code uses stack variables, so we need to simulate that.
    // I'll just model the logic.
    
    // Check if the token after condition is a statement block start (0x103)
    if (*(int*)(this + 0x0c) == 0x103) { // token type == '{' or similar
        // Save position for body
        *(int*)(this + 8) = *(int*)(this + 4);
        
        // Advance token if needed
        if (*(int*)(this + 0x14) == 0x11f) {
            *(int*)(this + 0x0c) = nextToken();
        } else {
            *(int*)(this + 0x0c) = *(int*)(this + 0x14);
            *(int*)(this + 0x10) = *(int*)(this + 0x18);
            *(int*)(this + 0x14) = 0x11f;
        }
        
        // Save current instruction index for body start
        int bodyInstrStart = bcCtx[6];
        bcCtx[7] = bodyInstrStart;
        
        // Push another scope for the body (maybe for variable declarations)
        // This secondary scope uses local variables stacked on the actual C stack (as was done for condition)
        // But the code does similar with &uStack_1c4.
        // I'll simplify: pushScope(bcCtx, someData);
        
        // Parse the statement block (FUN_006417c0(this))
        parseStatementBlock(this);
        
        // Pop the body scope (set bcCtx[0x14] = *puVar9 etc.)
        // Pop the instruction stack? Not exactly.
        
        // Restore body scope and continue/break targets
        // ...
        
        // After parsing body, expected closing token (0x106)
        if (*(int*)(this + 0x0c) == 0x106) {
            // Expected '}' or end of while
            // Similar token advance logic
            // ...
        } else {
            // Error: expected '}' to close while
            // Format error message with line number
            if (errorLineNum == *(int*)(this + 4)) {
                printError("`%s' expected", "`while'"); // actually uses format with %s
                // More complex formatting
            }
            // Print error using string formatting
            // ...
        }
    } else {
        // Error: expected `{` after while condition
        printError("`%s' expected", "`{'");
        // Goto label handling for error recovery
        // ...
    }
    
    // Pop the outer scope (while loop scope)
    // bcCtx[5] = *prevScope;
    // Fix up bytecode for continue/break jumps
    // ...
    
    // Ensure at least one instruction was emitted
    if (bodyInstrStart == bcCtx[6]) {
        // If body is empty, still need to update continue target?
        bcCtx[7] = bcCtx[6];
        restoreState(bcCtx);
        goto done;
    }
    
    // Fix up jump offsets (FUN_006426a0) – not fully understood
    fixupJumps(bcCtx, ...); // FUN_006426a0
    
done:
    // Update instruction store pointer
    bcCtx[7] = bcCtx[6];
    restoreState(bcCtx);
}

// Helper functions – not full implementations, just signatures for reference
void emitDebugInfo(int type, int data); // FUN_006438e0
void saveState(int* ctx); // FUN_00642880 – push state
void restoreState(int* ctx); // FUN_00642880 – restore state
void parseExpression(int* parser, int* result, int unknown); // FUN_0063fad0
void emitBoolCondition(); // FUN_006433b0
void printError(const char* format, ...); // FUN_00638b80 (and 00636c00 for format)
void parseStatementBlock(int* parser); // FUN_006417c0
void fixupJumps(int* ctx, int a, int b, int c, int d, int e, int f); // FUN_006426a0
int nextToken(); // FUN_00639c70 – advances and returns token type