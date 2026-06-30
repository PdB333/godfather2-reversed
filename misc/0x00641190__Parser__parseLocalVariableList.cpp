// FUNC_NAME: Parser::parseLocalVariableList

// Function address: 0x00641190
// Parses a comma-separated list of local variable names, adds them to the symbol table.
// Expects current token to be TOKEN_NAME (0x116). After parsing, expects comma or semicolon.
// Limit: 200 local variables.

#include <cstdint>

// Forward declarations of helper functions (assumed from the engine)
int32_t getNextToken(void* parserState); // FUN_00639c70
void* growArray(int32_t oldSize, int32_t newSize); // FUN_006279a0
void printError(const char* msg); // FUN_00638b80
void formatString(const char* fmt, ...); // FUN_00636c00
void handleError(int32_t errorCode); // FUN_00633920
int32_t getCurrentTokenValue(); // FUN_0063f220
void setSomething(int32_t val); // FUN_0063e260
void cleanup(); // FUN_0063def0

// Token constants
const int32_t TOKEN_NAME = 0x116;
const int32_t TOKEN_ASSIGN = 0x11f;
const int32_t TOKEN_COMMA = 0x2c;
const int32_t TOKEN_SEMICOLON = 0x3d;
const int32_t MAX_LOCAL_VARS = 200;

// Symbol table entry (12 bytes each)
struct SymbolEntry {
    int32_t nameIndex; // index into string table
    // ... other fields (type, etc.)
};

// Symbol table structure
struct SymbolTable {
    SymbolEntry* entries; // +0x18: pointer to array of entries
    int32_t capacity;     // +0x38: allocated capacity
    int32_t count;        // +0x30: current number of entries
    int32_t baseCount;    // +0x34: base count (e.g., number of already declared variables)
    // ... other fields
};

// Parser state structure (offsets relative to 'this')
struct ParserState {
    int32_t prevTokenType;   // +0x04
    int32_t prevTokenValue;  // +0x08
    int32_t currentTokenType; // +0x0c
    int32_t currentTokenValue; // +0x10
    int32_t nextTokenType;   // +0x14 (lookahead)
    int32_t nextTokenValue;  // +0x18
    SymbolTable* symTable;   // +0x1c
    int32_t extraField;      // +0x20 (used in error path)
};

void __thiscall Parser::parseLocalVariableList(ParserState* this) {
    int32_t count = 0; // number of variables processed in this list

    // Expect current token to be a name (identifier)
    while (this->currentTokenType == TOKEN_NAME) {
        int32_t nameIndex = this->currentTokenValue;
        this->prevTokenValue = this->currentTokenValue; // store previous token value

        // Check if next token is assignment (TOKEN_ASSIGN)
        if (this->nextTokenType == TOKEN_ASSIGN) {
            // Consume the assignment token and get the next token type
            this->currentTokenType = getNextToken(&this->currentTokenValue);
        } else {
            // Otherwise, shift tokens: next becomes current, and set next to assignment
            this->currentTokenType = this->nextTokenType;
            this->currentTokenValue = this->nextTokenValue;
            this->nextTokenType = TOKEN_ASSIGN;
        }

        SymbolTable* symTable = this->symTable;
        this->currentTokenType = this->currentTokenType; // redundant, but from decompiled

        // Check limit: total locals = symTable->baseCount + 1 + count
        if (MAX_LOCAL_VARS < symTable->baseCount + 1 + count) {
            goto tooManyLocals;
        }

        // Get the base pointer for the symbol table's entry array
        int32_t* basePtr = symTable->entries; // actually *symTable is a pointer to base? Decompiled: iVar2 = *piVar1
        // But careful: piVar1 is symTable, *piVar1 is the first int of symTable, which might be a pointer to another structure.
        // Let's assume symTable->entries is a pointer to an array of SymbolEntry, and we have a separate capacity/count.
        // Actually from decompiled: iVar2 = *piVar1; then *(int *)(iVar2 + 0x38) is capacity. So iVar2 is a pointer to a structure that has capacity at +0x38 and entries pointer at +0x18.
        // So we need to define a sub-structure. Let's call it VariableArray.
        struct VariableArray {
            int32_t* entries; // +0x18
            int32_t capacity; // +0x38
        };
        VariableArray* varArray = (VariableArray*)(symTable->entries); // Actually *symTable is the pointer to varArray? This is messy.
        // Better: Let's assume symTable points to a structure that contains a pointer to VariableArray at offset 0, and then fields at offsets 0x30, 0x34, etc.
        // Given the decompiled code: piVar1 = *(int **)(this + 0x1c); then iVar2 = *piVar1; so piVar1 is a pointer to a pointer? Actually piVar1 is a pointer to an int array. *piVar1 is the first int of that array, which is used as a pointer (iVar2). So piVar1 points to a structure that starts with a pointer to VariableArray.
        // Let's define:
        struct SymbolTableInternal {
            VariableArray* varArray; // +0x00
            int32_t count;           // +0x30 (piVar1[0xc])
            int32_t baseCount;       // +0x34 (piVar1[0xd])
            int32_t extraIndices[?]; // +0x2b8? (piVar1[0xae] = 174)
        };
        SymbolTableInternal* symTableInt = (SymbolTableInternal*)symTable;
        VariableArray* varArray = symTableInt->varArray;

        // Check if capacity is sufficient
        if (varArray->capacity < symTableInt->count + 1) {
            int32_t oldCapacity = varArray->capacity;
            int32_t newCapacity = oldCapacity * 2;
            if (newCapacity < 4) {
                newCapacity = 4;
            } else if (oldCapacity > 0x3ffffffd) {
                // Overflow, handle error
                handleError((int32_t)this); // actually uses unaff_EDI
                // goto error
            }
            // Reallocate array (each entry 12 bytes)
            void* newEntries = growArray(oldCapacity * 12, newCapacity * 12);
            varArray->capacity = newCapacity;
            varArray->entries = (int32_t*)newEntries;
        }

        // Store the name index into the entries array at current count
        varArray->entries[symTableInt->count * 3] = nameIndex; // each entry is 12 bytes, so index * 3 (since int32_t is 4 bytes)
        // Actually decompiled: *(undefined4 *)(*(int *)(iVar2 + 0x18) + piVar1[0xc] * 0xc) = uVar5;
        // So entries is a byte array, each entry 12 bytes. We'll store as int32_t at offset count*12.
        // But we'll just store as int32_t for simplicity.

        // Increment count in symbol table
        int32_t currentCount = symTableInt->count;
        symTableInt->count = currentCount + 1;

        // Store the index of this new variable in a separate list (for ordering?)
        // piVar1[piVar1[0xd] + count + 0xae] = iVar2;
        // piVar1[0xd] is baseCount, count is local count, 0xae is offset 174 ints = 0x2b8 bytes
        symTableInt->extraIndices[symTableInt->baseCount + count] = currentCount;

        // If current token is not comma, break out of loop
        if (this->currentTokenType != TOKEN_COMMA) {
            goto afterLoop;
        }

        // Advance token state for comma
        this->prevTokenValue = this->currentTokenValue;
        count = count + 1; // increment local count

        // Get next token (should be another name)
        if (this->nextTokenType == TOKEN_ASSIGN) {
            this->currentTokenType = getNextToken(&this->currentTokenValue);
        } else {
            this->currentTokenType = this->nextTokenType;
            this->currentTokenValue = this->nextTokenValue;
            this->nextTokenType = TOKEN_ASSIGN;
        }
    }

    // If we exit the while loop because current token is not NAME, it's an error
    printError("<name> expected");
    // fall through to error handling? Actually the code goes to error label directly.

tooManyLocals:
    // Error: too many local variables
    int32_t errorMsg = formatString("too many %s (limit=%d)", "local variables", MAX_LOCAL_VARS);
    printError(errorMsg);
    handleError((int32_t)this);

afterLoop:
    // After parsing the list, handle possible semicolon or end of statement
    if (this->currentTokenType == TOKEN_SEMICOLON) {
        this->prevTokenValue = this->currentTokenValue;
        if (this->nextTokenType == TOKEN_ASSIGN) {
            this->currentTokenType = getNextToken(&this->currentTokenValue);
            int32_t val = getCurrentTokenValue();
            setSomething(val);
        } else {
            this->currentTokenType = this->nextTokenType;
            this->nextTokenType = TOKEN_ASSIGN;
            this->currentTokenValue = this->nextTokenValue;
            int32_t val = getCurrentTokenValue();
            setSomething(val);
        }
    } else {
        // No semicolon, just get something
        int32_t val = 0;
        setSomething(val);
    }
    cleanup();
}