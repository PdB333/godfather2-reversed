// FUNC_NAME: Lexer::readToken
// Address: 0x00639c70
// Role: Main tokenizer function for a custom scripting language (likely EARS script). Returns a token ID.
// Returns 0x11f on EOF, 0x11d for numbers, 0x11e for strings, 0x116 for identifiers, and compound tokens for operators.

enum TokenType : uint {
    TK_INVALID      = 0,
    TK_IDENTIFIER   = 0x116,
    TK_NUMBER       = 0x11d,
    TK_STRING       = 0x11e,
    TK_EQ           = 0x119,  // ==
    TK_NE           = 0x11a,  // !=
    TK_LE           = 0x11b,  // <=
    TK_GE           = 0x11c,  // >=
    TK_ELIPSIS      = 0x118,  // ...
    TK_RANGE        = 0x117,  // .. (two dots)
    TK_EOF          = 0x11f,
    // Keywords are returned as base_token + 0x100 (handled by caller)
};

struct InputBuffer {
    int remaining;          // [0] bytes left in buffer
    byte* bufferPtr;        // [4] current read pointer
    // [8] maybe vtable or function pointer for refill
    // [12] user data for refill
};

struct Lexer {
    uint currentChar;       // [0] *in_EAX in decompile
    // ... other fields at offsets [8], [9], [10]?
    InputBuffer* inputBuf;  // [9] (offset 0x24 in 32-bit)
    void* keywordTable;     // [8] maybe a hash table or tree
    void* identifierTable;  // [10] maybe string pool
    // Note: offsets are approximate based on usage.
};

// Forward declarations
uint readNextChar(Lexer* lex);
uint peekNextChar(Lexer* lex); // actually consumes? No, we model separately
bool isDigit(uint c);
bool isAlpha(uint c);
bool isSpace(uint c);
bool isCntrl(uint c);
uint parseNumber(int mode, int* outToken);
uint parseString(uint quoteChar, int* outToken);
uint lookupIdentifier(Lexer* lex, uint* outIdNode);
void skipLineComment(Lexer* lex);
void skipBlockComment(Lexer* lex, int* outToken); // FUN_00639340
void error(const char* format, ...);
void consumeChar(Lexer* lex);
void refillBuffer(Lexer* lex);
void setCurrentChar(Lexer* lex, uint c);
uint lexerReadToken(Lexer* lex, int* outTokenType);

uint lexerReadToken(Lexer* lex, int* outTokenType) {
    // This corresponds to FUN_00639c70
    for (;;) {
        uint c = lex->currentChar;
        switch (c) {
        default: {
            // Not a special character
            if (isSpace(c)) {
                // Skip whitespace and continue loop
                goto consumeAndLoop;
            }
            if (isDigit(c)) {
                // Number literal
                parseNumber(0, outTokenType); // FUN_00638ee0(0, param_1)
                return TK_NUMBER;
            }
            if (isAlpha(c) || c == '_') {
                // Identifier or keyword
                uint idNode = lookupIdentifier(lex); // FUN_00638dc0() returns some identifier
                int result = lookupKeyword(lex->keywordTable, idNode, lex->identifierTable); // FUN_00638920
                if (*(byte*)(result + 6) != 0) {
                    // It's a keyword with a special token > 0x100
                    uint token = *(byte*)(result + 6) + 0x100;
                    return token;
                }
                // Regular identifier
                *outTokenType = result;
                return TK_IDENTIFIER;
            }
            if (isCntrl(c)) {
                error("char(%d)", c); // FUN_00636c00
                reportError("invalid control char", ...); // FUN_00638b20
            }
            // For any other character, just consume it and return it?
            // Actually the default case: after error it proceeds to consume next char
            // But from decompile, it falls through to the consume+return path
            // We'll fall through to consumeAndReturn
            goto consumeAndReturn;
        }
        case 10: // newline
            skipLineComment(lex); // FUN_00638c40()? No, that's for line continuation? Actually it looks like a line increment function. We'll treat as newline handling.
            // In the decompile, case 10 calls FUN_00638c40 and then continues loop.
            break;

        case '"':
        case '\'':
            // String literal
            parseString(c, outTokenType); // FUN_00639730(c, param_1)
            return TK_STRING;

        case '-': {
            // Possible comment or minus operator
            uint next = peekNextChar(lex);
            if (next != '-') {
                // Not comment, return minus operator
                setCurrentChar(lex, next); // Actually already consumed
                return '-';
            }
            // It's a comment starting with --
            // Check for block comment with [[
            consumeChar(lex); // consume second '-'
            uint after = peekNextChar(lex);
            if (after == '[') {
                // Possible block comment: --[[ ... ]]
                consumeChar(lex); // consume '['
                // Decompiled: call FUN_00639340(0) with argument? Actually the decompile shows FUN_00639340(0) when '<[' case
                // But here it's after '-' and we already have two '-' and a '['? Wait, the decompile for '-' case:
                // It first consumes the first '-', then checks if next is '-', then consumes that, then checks if next is '[', then calls FUN_00639340(0)
                // So yes, it's --[[ (long comment)
                skipBlockComment(lex, outTokenType); // FUN_00639340(0) but with argument actually param_1? Clarify
                // After block comment, loop continues
            } else {
                // Line comment: skip to end of line
                skipLineComment(lex); // Decompiled: while not newline and not EOF, consume
            }
            // After handling comment, currentChar is updated, continue loop
            break;
        }

        case '.':
            // Handle dot(s)
            // ...
            // Complex logic for float, range, ellipsis
            // We'll compress: parse dot sequence
            // Actually decompile is long but we can reconstruct:
            {
                uint next = peekNextChar(lex);
                if (next == '.') {
                    // ... sequence
                    consumeChar(lex); // consume second dot
                    uint third = peekNextChar(lex);
                    if (third == '.') {
                        consumeChar(lex); // consume third dot
                        return TK_ELIPSIS;
                    } else {
                        // Just two dots: ..
                        return TK_RANGE;
                    }
                } else if (isDigit(next)) {
                    // Float number: .digit
                    parseNumber(1, outTokenType); // float mode
                    return TK_NUMBER;
                } else {
                    // Single dot
                    return '.';
                }
            }

        case '<':
        case '>':
        case '=':
        case '!':
        case '~':
            // Two-character operators with '='
            {
                uint next = peekNextChar(lex);
                if (next == '=') {
                    consumeChar(lex);
                    uint combinedToken;
                    switch (c) {
                    case '<': combinedToken = TK_LE; break;
                    case '>': combinedToken = TK_GE; break;
                    case '=': combinedToken = TK_EQ; break;
                    case '!': combinedToken = TK_NE; break;
                    case '~': combinedToken = 0x11c; // ~=, maybe TK_MATCH?
                    default: combinedToken = 0;
                    }
                    return combinedToken;
                } else {
                    // Single char
                    return c;
                }
            }

        case '[': {
            // Double bracket for block comment?
            uint next = peekNextChar(lex);
            if (next == '[') {
                consumeChar(lex);
                skipBlockComment(lex, outTokenType); // FUN_00639340(param_1) -> param_1 is used?
                // After block comment, loop continues
                break;
            } else {
                return '['; // Normal bracket
            }
        }

        case 0xffffffff:
            return TK_EOF;

        } // end switch

        // After handling special tokens that don't return, we consume a character and continue loop
        // Actually the code for whitespace and control chars does a specific consume pattern
        consumeAndLoop:
        consumeChar(lex);
        continue;

        consumeAndReturn:
        // For default case where we want to return the current character itself (like single char tokens)
        // But the decompile for default case actually consumes a char and then returns it? Let's see:
        // In default case after error, it does the consume-and-return pattern (in_EAX[9] stuff)
        // That pattern is exactly the same as the whitespace consume pattern except it returns the current char.
        // So for any character that is not handled, we consume it and return it as a token.
        // This would handle single char operators like +, *, etc.
        consumeChar(lex);
        return c; // return the consumed character as the token?
    } // end for(;;)
}