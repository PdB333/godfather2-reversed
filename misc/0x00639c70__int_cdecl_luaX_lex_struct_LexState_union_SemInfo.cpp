// Xbox PDB: int __cdecl luaX_lex(struct LexState *,union SemInfo *)
// FUNC_NAME: Lexer::nextToken

#include <cstdint>

// Forward declarations for utility functions
int _isspace(int ch);
int _isdigit(int ch);
int _isalpha(int ch);
int _iscntrl(int ch);
void Lexer_handleNewline();
void Lexer_parseString(int quoteChar, int* tokenValue);
void Lexer_parseNumber(int base, int* tokenValue);
int Lexer_refillBuffer(void* buffer, int size, int* bytesRead);
int Lexer_lookupIdentifier(int hashTable, int key, int value);
int Lexer_getChar(void* context); // Actually uses buffer structure
void Lexer_formatError(const char* fmt, int charVal, int line);
void Lexer_parseComment(int* tokenValue);
int Lexer_buildKeywordTable(); // returns id

// Token codes
enum Token {
    TOKEN_EOF = 0x11f,
    TOKEN_NUMBER = 0x11d,
    TOKEN_STRING = 0x11e,
    TOKEN_IDENTIFIER = 0x116,
    TOKEN_ELLIPSIS = 0x118,
    TOKEN_DOT = 0x117,
    TOKEN_LE = 0x11b,
    TOKEN_GE = 0x11a,
    TOKEN_EQ = 0x119,
    TOKEN_NE = 0x11c,
    TOKEN_ASSIGN = 0x3d,
    TOKEN_LBRACKET = 0x5b,
    TOKEN_NEWLINE = 10,
    // Single character tokens are returned as their ASCII value
};

// Buffer structure for input stream (size=unknown)
struct InputBuffer {
    int remaining;       // +0x00
    char* current;       // +0x04
    int (*refillFunc)(int, void*, int*); // +0x08 (callback)
    void* stream;        // +0x0C (handle)
};

// Lexer context structure (size at least 11 ints)
struct LexerContext {
    int currentChar;           // +0x00 (current lookahead character)
    uint32_t hashTable;        // +0x20 (index 8)
    InputBuffer* buffer;       // +0x24 (index 9) 
    uint32_t identifierTable;  // +0x28 (index 10)
    // ... other fields
};

// Main tokenizer function
// Returns token type and optionally stores token data in tokenValue.
uint32_t Lexer_nextToken(LexerContext* ctx, int* tokenValue)
{
    while (true) {
        if (ctx->currentChar != '\n') {
            // Check for whitespace
            if (_isspace(ctx->currentChar) == 0) {
                if (_isdigit(ctx->currentChar)) {
                    // Parse decimal number
                    Lexer_parseNumber(0, tokenValue);
                    return TOKEN_NUMBER;
                }
                if (_isalpha(ctx->currentChar) || ctx->currentChar == '_') {
                    // Could be identifier or keyword
                    int keywordTable = Lexer_buildKeywordTable(); // get keyword table id
                    int entry = Lexer_lookupIdentifier(ctx->hashTable, 
                                                       *(uint32_t*)(ctx->identifierTable),
                                                       keywordTable);
                    if (*(uint8_t*)(entry + 6) != 0) {
                        // It's a keyword, return its token code (0x100+)
                        return *(uint8_t*)(entry + 6) + 0x100;
                    }
                    // Store identifier index and return ID token
                    *tokenValue = entry;
                    return TOKEN_IDENTIFIER;
                }
                // Control character? Check iscntrl (but not for accepted chars)
                if (_iscntrl(ctx->currentChar)) {
                    Lexer_formatError("char(%d)", ctx->currentChar, 
                                      *(int*)(ctx->buffer + 8)); // line number?
                    Lexer_formatError("invalid control char", /**/, /**/);
                }
                // Consume one character and return it as token (single char)
                Lexer_advanceChar(ctx);
                unsigned char ch = ctx->currentChar; // actually the consumed char
                // The consumed character is returned as token?
                // Actually the function returns the consumed char if not special
                return (uint32_t)ch;
            }
            // It's whitespace, skip it by consuming a character
            Lexer_advanceChar(ctx);
        }
        else {
            // Newline handling
            Lexer_handleNewline();
        }
    }
}

// Helper to consume one character from buffer
// Updates ctx->buffer and ctx->currentChar
void Lexer_advanceChar(LexerContext* ctx) {
    InputBuffer* buf = ctx->buffer;
    if (buf->remaining > 0) {
        buf->remaining--;
        ctx->currentChar = (uint8_t)*buf->current;
        buf->current++;
    } else {
        // Need to refill buffer
        int bytesRead;
        uint8_t* data = (uint8_t*)buf->refillFunc(0, buf->stream, &bytesRead);
        if (data != nullptr && bytesRead > 0) {
            buf->current = (char*)data;
            buf->remaining = bytesRead - 1;
            ctx->currentChar = *data;
            buf->current++;
        } else {
            ctx->currentChar = 0xFFFFFFFF; // EOF marker
        }
    }
}