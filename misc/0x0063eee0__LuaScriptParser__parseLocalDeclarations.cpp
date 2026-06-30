// FUNC_NAME: LuaScriptParser::parseLocalDeclarations
struct LuaScriptParser {
    // offsets relative to this pointer
    // +0x0: vtable
    int* vtable;                    // +0x00
    int lastToken;                  // +0x04
    int currentToken;               // +0x08
    int tokenType;                  // +0x0C
    int tokenValue;                 // +0x10
    int lookaheadType;              // +0x14
    int lookaheadValue;             // +0x18
    int* variableTable;             // +0x1C
    void* allocator;                // +0x20
};

struct VarTable {
    // +0x00: first element? (some array)
    int field_0x00;
    int varCount;                   // +0x0C
    int totalVars;                  // +0x0D
    int* varNamesBuffer;            // +0x18
    int varNamesCapacity;           // +0x38
    int varIndices[1];              // +0xAE (actually array of size totalVars + number of new vars)
};

// Helper functions (from callees)
extern "C" int FUN_00639c70(void* parser);          // likely readNextToken
extern "C" int* FUN_00627930(void* allocator, int* buffer, int* capacity, int size, void* tag); // realloc
extern "C" void FUN_00638b80(const char* msg);      // errorPrint
extern "C" const char* FUN_00636c00(const char* fmt, ...); // formatError
extern "C" void FUN_0063e340(int flag);             // cleanup

void __thiscall LuaScriptParser::parseLocalDeclarations() {
    int newVarCount = 0;
    int hasSeparator = 0;               // local_8

    if (this->tokenType != 0x29) {      // 0x29 = '('
        while (this->tokenType == 0x116) { // 0x116 = 'local' keyword
            int varTokenValue = this->tokenValue;          // uVar5
            this->currentToken = this->lastToken;          // move token

            if (this->lookaheadType == 0x11f) { // 0x11f = '=' sign
                varTokenValue = FUN_00639c70(this);       // read the expression token
            } else {
                varTokenValue = this->lookaheadValue;      // take lookahead value
                this->tokenValue = this->lookaheadValue;   // shift lookahead
                this->lookaheadType = 0x11f;               // mark as used
            }
            this->tokenType = varTokenValue;

            VarTable* varTable = this->variableTable;     // piVar1

            if (200 < varTable->totalVars + 1 + newVarCount) {
                // too many locals
                const char* errMsg = FUN_00636c00("too many %s (limit=%d)", "local variables", 200);
                FUN_00638b80(errMsg);
                __asm int 3;  // trigger breakpoint/abort
                return;
            }

            // Ensure varNamesBuffer capacity
            int currentCapacity = varTable->varNamesCapacity;
            if (*reinterpret_cast<int*>(varTable->field_0x00 + 0x38) < varTable->varCount + 1) {
                int* newBuffer = FUN_00627930(
                    this->allocator,
                    varTable->varNamesBuffer,
                    &currentCapacity,  // capacity variable
                    0xC,               // element size (12 bytes)
                    &DAT_00e2f044      // allocation tag
                );
                varTable->varNamesBuffer = newBuffer;
            }

            // Store varTokenValue into varNamesBuffer at offset varCount * 12
            varTable->varNamesBuffer[varTable->varCount * 3] = varTokenValue; // each entry is 12 bytes (3 ints)

            int oldVarCount = varTable->varCount;
            varTable->varCount = oldVarCount + 1;

            // Store the index into varIndices array
            varTable->varIndices[varTable->totalVars + newVarCount] = oldVarCount;

            newVarCount++;

            // Check for comma or end
            if (this->tokenType == 0x2C) { // comma
                this->currentToken = this->lastToken; // move token
                if (this->lookaheadType == 0x11F) {
                    this->tokenType = FUN_00639c70(this);
                } else {
                    this->tokenType = this->lookaheadType;
                    this->tokenValue = this->lookaheadValue;
                    this->lookaheadType = 0x11F;
                }
            } else {
                break; // no comma -> exit loop
            }
        }

        // After loop, expect token 0x118 (e.g., 'end' or newline)
        if (this->tokenType != 0x118) {
            FUN_00638b80("<name> or `...' expected");
            return;
        }
        this->currentToken = this->lastToken; // shift token
        hasSeparator = 1;

        // Read next token
        if (this->lookaheadType == 0x11F) {
            this->tokenType = FUN_00639c70(this);
        } else {
            this->tokenType = this->lookaheadType;
            this->tokenValue = this->lookaheadValue;
            this->lookaheadType = 0x11F;
        }
    }

    // Final cleanup
    FUN_0063e340(hasSeparator);
}