// FUNC_NAME: ScriptParser::parseLocalVariableList

// Address: 0x006409b0
// Parses a comma-separated list of local variable declarations inside a script block.
// Handles token sequences for variable names and emits code for a generator state.
// Part of the EARS script compiler/bytecode generator.

void __thiscall ScriptParser::parseLocalVariableList(int *this, int param_1) {
    int *codeBuffer;                 // [EBP-?] unaff_EBX (symbol table/code output)
    int *generatorState;             // [EBP-?] from this[7] -> piVar1
    int generatorIndex;              // iVar2
    int token;                       // iVar3, iVar5, iVar6, etc.
    int localVarCount;               // iVar7
    int *parserState;                // piVar9
    int extra_ecx;                   // extraout_ECX
    
    generatorState = (int *)this[7];            // +0x1c? generator state struct
    generatorIndex = generatorState[9];         // +0x24?
    
    // Debug scope begin: "for generator"
    int debugId = FUN_00638920(this[8], "(for generator)", 0xf, 0);  // +0x20? debug context
    FUN_0063de90(debugId);
    
    // Debug scope for "for state"
    debugId = FUN_00638920(this[8], "(for state)", 0xb, 1);
    FUN_0063de90(debugId);
    
    // Emit opcode for something (param_1, 2)
    FUN_0063de90(param_1, 2);
    
    int localVarCount = 3;  // initial count includes implicit locals?
    
    // Parse comma-separated variable names: token 0x2c = ','
    while ( (token = this[3]) == 0x2c ) {
        codeBuffer = (int *)0x11f;  // placeholder, actually set later
        this[2] = this[1];          // advance token pointer?
        
        // Get next token (skip comma)
        if (this[5] == 0x11f) {     // token type 0x11f = "identifier"
            token = FUN_00639c70(this + 4);  // get identifier token
            this[3] = token;
        } else {
            this[3] = this[5];
            this[4] = this[6];
            this[5] = 0x11f;        // reset to "identifier"
        }
        
        // Expect identifier (0x116 = name token)
        if (this[3] != 0x116) {
            FUN_00638b80("<name> expected");
            goto error_too_many_locals;
        }
        
        int nameToken = this[4];    // actual name string/index
        
        this[2] = this[1];          // advance again
        if (this[5] == 0x11f) {
            token = FUN_00639c70(this + 4);
            this[3] = token;
        } else {
            this[3] = this[5];
            this[4] = this[6];
            this[5] = 0x11f;
        }
        
        codeBuffer = (int *)this[7];    // +0x1c: code/generator buffer
        if (localVarCount + codeBuffer[0xd] + 1 > 200) {  // +0x34: current local count limit (200)
            goto error_too_many_locals;
        }
        
        // Grow symbol array if needed
        int *symTable = (int *)*codeBuffer;       // deref? Actually *codeBuffer leads to some struct
        if (symTable[0x38] < codeBuffer[0xc] + 1) { // +0xe0? need more space
            int oldCapacity = symTable[0x38];
            int newCapacity = oldCapacity * 2;
            if (newCapacity < 4)
                newCapacity = 4;
            if (oldCapacity >= 0x3ffffffe) {
                if (oldCapacity >= 0x7ffffff9) {
                    goto mem_growth_error;
                }
                newCapacity = 0x7ffffffd;
            }
            int *newArray = FUN_006279a0(oldCapacity * 0xc, newCapacity * 0xc);
            symTable[0x38] = newCapacity;
            symTable[0x18] = (int)newArray;   // +0x60? store new array pointer
        }
        
        // Store variable name token into array
        int *arrayBase = (int *)symTable[0x18];
        arrayBase[codeBuffer[0xc] * 3] = nameToken;  // each entry 12 bytes
        int currentIndex = codeBuffer[0xc];
        codeBuffer[0xc] = currentIndex + 1;
        codeBuffer[codeBuffer[0xd] + localVarCount + 0xae] = currentIndex;  // store variable index in some map
        
        localVarCount++;
    }
    
    // After loop, expect token 0x10b (maybe end-of-statement, like ';')
    if (this[3] != 0x10b) {
        // error: expected something
        int errorId = FUN_00636c00("`%s' expected", PTR_DAT_00e2a8e8);
        int errorAddr = FUN_00638b80(errorId);
        goto handle_error;
    }
    
    // Consume the 0x10b token
    this[2] = this[1];
    if (this[5] == 0x11f) {
        // error path
        goto get_next_token;
    }
    this[3] = this[5];
    this[4] = this[6];
    this[5] = 0x11f;
    
    // Process for loop body: generate code for generator state
    while (1) {
        codeBuffer = (int *)this[1];
        int exprId = FUN_0063f220();      // get expression/condition
        FUN_0063e260(localVarCount, exprId);
        int *someStruct = (int *)*parserState;  // piVar9 = *this?
        int complexity = someStruct[9] + 3;
        if (complexity <= (int)(uint)*(byte *)((int)(*codeBuffer) + 0x47)) {
            // complexity check passed
            break;
        }
        if (complexity < 0xfa) {
            parserState = (int *)parserState[3];
            FUN_00638b80("function or expression too complex");
            // fall through to error handler
        }
        // Actually goto error label below
    }
    
    // Emit finalization code
    int opcode = (generatorIndex << 0x18) | 0x7fff9e;
    FUN_006438e0(opcode, *(int *)(parserState[3] + 8));
    FUN_00640550(generatorIndex, codeBuffer, localVarCount, 0);
    return;

error_too_many_locals:
    int errMsg = FUN_00636c00("too many %s (limit=%d)", "local variables", 200);
    FUN_00638b80(errMsg);
    parserState = this;
    mem_growth_error:
    FUN_00633920(parserState, &DAT_00e2f044);  // error handling
    return;

get_next_token:
    token = FUN_00639c70(this + 4);
    this[3] = token;
    goto after_get_token;  // not really used, but for flow

handle_error:
    // Set complexity error marker
    *(char *)(extra_ecx + 0x47) = (char)errorAddr;
    return;
}