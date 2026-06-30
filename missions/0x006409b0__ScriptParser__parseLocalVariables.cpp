// FUNC_NAME: ScriptParser::parseLocalVariables
// Function address: 0x006409b0
// Parses local variable declarations, handling "for generator" and "for state" scopes.
// Token constants: 0x11f = TOKEN_NONE, 0x116 = TOKEN_IDENTIFIER, 0x10b = TOKEN_EQUALS, 0x2c = TOKEN_SEMICOLON

#define TOKEN_NONE 0x11f
#define TOKEN_IDENTIFIER 0x116
#define TOKEN_EQUALS 0x10b
#define TOKEN_SEMICOLON 0x2c
#define MAX_LOCAL_VARS 200

void ScriptParser::parseLocalVariables(int codeEmitter) {
    // 'this' is in unaff_EDI, a parser state structure
    // offsets: [1] = previousTokenType, [2] = savedTokenType, [3] = currentTokenType,
    //          [4] = currentTokenValue, [5] = peekTokenType, [6] = peekTokenValue,
    //          [7] = localVarTable (int*), [8] = errorContext (ptr)

    int* varTable = reinterpret_cast<int*>(this->field7); // +0x1c (offset of field7)
    int tableId = varTable[9]; // some table index (maybe scope ID)

    // Push scope names for generator and state
    std::string* genLabel = createString(formatString("(for generator)"));  // FUN_00638920
    pushString(genLabel);  // FUN_0063de90
    std::string* stateLabel = createString(formatString("(for state)"));
    pushString(stateLabel);
    pushValue(codeEmitter, 2); // push something with argument 2

    int varCount = 3; // starting index for local variable entries (0,1,2 reserved?)

    // Loop while current token is a semicolon (token type 0x2c)
    while (this->currentTokenType == TOKEN_SEMICOLON) {
        // Reset to previous token? Actually [2] = [1], [1] might be previous token
        this->savedTokenType = this->previousTokenType;
        this->currentTokenType = TOKEN_NONE;

        // Expect identifier for variable name
        if (this->peekTokenType == TOKEN_NONE) {
            this->currentTokenType = getNextToken(&this->field4);  // FUN_00639c70
        } else {
            this->currentTokenType = this->peekTokenType;
            this->currentTokenValue = this->peekTokenValue;
            this->peekTokenType = TOKEN_NONE;
        }

        if (this->currentTokenType != TOKEN_IDENTIFIER) {
            errorPrint("<name> expected");  // FUN_00638b80
            goto cleanup;
        }

        int varNameIndex = this->currentTokenValue; // identifier index

        // Next token: expect another identifier (variable type?)
        this->savedTokenType = this->previousTokenType;
        if (this->peekTokenType == TOKEN_NONE) {
            this->currentTokenType = getNextToken(&this->field4);
        } else {
            this->currentTokenType = this->peekTokenType;
            this->currentTokenValue = this->peekTokenValue;
            this->peekTokenType = TOKEN_NONE;
        }

        int varTypeIndex = this->currentTokenValue; // for now, second identifier index

        // Check limit of local variables
        int currentSlot = varTable[0xd]; // something like current slot count?
        if (200 < currentSlot + 1 + varCount) {
            std::string* errMsg = formatError("too many %s (limit=%d)", "local variables", 200);  // FUN_00636c00
            errorPrint(errMsg);
            goto cleanup;
        }

        // Ensure variable array has capacity
        int* parentTable = reinterpret_cast<int*>(varTable[0]); // +0x00
        int capacity = parentTable[0x38 / 4]; // offset +0x38 = capacity
        if (capacity < varTable[0xc] + 1) { // varTable[0xc] = current count
            int newCapacity;
            int oldCapacity = parentTable[0x38 / 4];
            if (oldCapacity * 2 < 4) {
                newCapacity = 4;
            } else if (oldCapacity < 0x3ffffffe) {
                newCapacity = oldCapacity * 2;
            } else if (oldCapacity < 0x7ffffff9) {
                newCapacity = 0x7ffffffd;
            } else {
                goto fail_cleanup;
            }
            int* newArray = reinterpret_cast<int*>(allocateArray(oldCapacity * 12, newCapacity * 12));  // FUN_006279a0
            parentTable[0x38 / 4] = newCapacity;
            parentTable[0x18 / 4] = reinterpret_cast<int>(newArray);
        }

        // Store variable info: index = varNameIndex? Actually iVar6 from earlier was varTypeIndex? The code stored iVar6 which was set to varTypeIndex.
        int* varArray = reinterpret_cast<int*>(parentTable[0x18 / 4]);
        int slotIndex = varTable[0xc];
        varArray[slotIndex * 3] = varTypeIndex; // store type index? Actually each entry is 12 bytes (3 ints)
        varTable[0xc] = slotIndex + 1;
        // Map variable name index to slot index
        varTable[0xae + varCount] = slotIndex; // offset +0xae = slot mapping for variable at count
        varCount++;
    }

    // After the semicolon loop, expect '=' (token 0x10b) for initializations
    if (this->currentTokenType == TOKEN_EQUALS) {
        this->savedTokenType = this->previousTokenType;
        if (this->peekTokenType == TOKEN_NONE) {
            this->currentTokenType = getNextToken(&this->field4);
        } else {
            this->currentTokenType = this->peekTokenType;
            this->currentTokenValue = this->peekTokenValue;
            this->peekTokenType = TOKEN_NONE;
        }
        // Process each initialization expression
        while (true) {
            int* curContext = reinterpret_cast<int*>(this->field1); // something
            std::string* symName = newSymbol();  // FUN_0063f220
            assignSymbolValue(this->field8, symName);  // FUN_0063e260
            int* parentTable2 = reinterpret_cast<int*>(varTable[0]); // +0x00
            int complexity = parentTable2[9] + 3; // offset +0x24? 
            if (complexity > static_cast<uint8_t>(*(reinterpret_cast<char*>(parentTable2) + 0x47))) {
                break;
            }
            if (complexity >= 0xfa) {
                // Too complex
                varTable = reinterpret_cast<int*>(varTable[3]); // dereference with offset +0x0c?
                errorPrint("function or expression too complex");
                goto cleanup;
            }
        }
    } else {
        std::string* errMsg = formatError("`%s' expected", "=");  // PTR_DAT_00e2a8e8 likely "="
        int errorCode = errorPrint(errMsg);
        // Store error code into something
        *(reinterpret_cast<char*>(this->field9) + 0x47) = static_cast<char>(errorCode);
    }

cleanup:
    // Emit bytecode for the parsed block
    emitBytecode((tableId << 24) | 0x7fff9e, *(reinterpret_cast<int*>(varTable[0]) + 0x08));  // FUN_006438e0
    processBlock(tableId, varTable, this->field8, 0);  // FUN_00640550
    return;

fail_cleanup:
    cleanupHandler(this->field8, &DAT_00e2f044);  // FUN_00633920 (likely longjmp or error recovery)
    goto cleanup;
}