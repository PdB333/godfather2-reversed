// FUNC_NAME: Parser::parseExpression
// Address: 0x0063fad0
// Role: Recursive descent expression parser (Pratt parser) for scripting language
// Parser state object fields (offsets):
// +0x00: vtable (not used)
// +0x04: savedToken (backup token for operator)
// +0x08: savedTokenValue (backup value for operator)
// +0x0c: currentToken (current token type)
// +0x10: tokenValue (integer value or pointer)
// +0x14: nextTokenType (peeked token type)
// +0x18: nextTokenValue (peeked token value)
// +0x30: syntaxDepth (recursion depth limit)

#include <cstdint>

// External functions (from same parser module)
void parserError(const char* msg);                     // FUN_00638b80
void parsePrimary(Parser* this);                       // FUN_0063f750
void nextToken();                                      // FUN_0063db50
void buildUnaryExpression(bool unaryMinus);            // FUN_00643560
int getCurrentToken();                                 // FUN_0063f930
int lexGetNextToken(void* lexerState);                 // FUN_00639c70 (returns token type)
void consumeToken();                                   // FUN_00643610
void emitOperator(int opToken, int* outValue);         // FUN_00643700

// Precedence table: two bytes per entry (left, right) indexed by token type
extern const uint8_t precedenceTable[][2]; // DAT_00e2a85c

// __thiscall: this in ECX
int Parser::parseExpression(Parser* this, int* outValue, int precedence) {
    int currentToken;
    int resultToken;
    bool unaryFlag = true; // uVar3 = 1

    this->syntaxDepth++;
    if (this->syntaxDepth > 200) {
        parserError("too many syntax levels");
    }

    if (this->currentToken == 0x2d) {             // '-'
        unaryFlag = false;                         // unary minus
    }
    else if (this->currentToken != 0x10e) {        // 0x10e = unary minus token? (different from '-')
        // Prefix expression (no unary operator)
        parsePrimary(this);
        goto mainLoop;
    }

    // Unary operator encountered ('-' or 0x10e)
    nextToken();
    parseExpression(this, outValue, 8);           // recursive with precedence 8
    buildUnaryExpression(unaryFlag);

mainLoop:
    currentToken = getCurrentToken();
    while (currentToken != 0xe && (precedence < (uint8_t)precedenceTable[currentToken * 2][0])) {
        // Save token info for backup
        this->savedTokenValue = this->savedToken;   // +0x08 = +0x04
        if (this->nextTokenType == 0x11f) {         // 0x11f = marker for "needs lexer read"
            this->currentToken = lexGetNextToken(&this->tokenValue); // +0x10
        }
        else {
            this->currentToken = this->nextTokenType;
            this->tokenValue = this->nextTokenValue;
            this->nextTokenType = 0x11f;             // reset marker
        }
        consumeToken();
        resultToken = parseExpression(this, outValue, precedenceTable[currentToken * 2][1]);
        emitOperator(currentToken, outValue);
        currentToken = resultToken;                  // return token from inner parse
    }

    this->syntaxDepth--;
    return currentToken;
}