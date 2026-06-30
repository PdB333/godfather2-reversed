// FUNC_NAME: ScriptParser::parseFunctionCall

class ScriptParser {
public:
    // Token state offsets from this pointer:
    // +0x04: tokenValue or previous token
    // +0x08: extra token data (e.g. previous token's value)
    // +0x0C: current token type
    // +0x10: token data pointer? (buffer for next token)
    // +0x14: next token type (peeked)
    // +0x18: token data buffer (for two-token lookahead)
    
    // Token constants
    enum TokenType {
        TOKEN_OPEN_PAREN = 0x28,   // '('
        TOKEN_CLOSE_PAREN = 0x29,  // ')'
        TOKEN_STATEMENT_END = 0x106, // e.g., ';' or keyword
        TOKEN_INVALID = 0x11F
    };

    void parseFunctionCall(int parseNested, int lineNumber);
    
private:
    // Helper functions (from decompiled calls)
    void initParserState();                    // FUN_0063e530
    int getNextToken(int* tokenBuffer);        // FUN_00639c70 - returns new token type
    void parseNestedBlock();                   // FUN_0063dfb0
    void parseSomethingAfterOpenParen();       // FUN_0063eee0 (probably parses the argument list)
    void advanceLexer();                       // FUN_006417c0 - moves to next token from lexer
    void finalizeParseAfterCloseParen();       // FUN_0063e5a0
    void cleanupParserState(int* buffer);      // FUN_0063e460
    void reportError(const char* format, ...); // FUN_00636c00 / FUN_00638b80
    
    // Internal state (local buffer, 374 ints = ~1496 bytes)
    int parserBuffer[374]; // first element is often a pointer to a sub-structure
};

void ScriptParser::parseFunctionCall(int parseNested, int lineNumber) {
    initParserState();
    
    // Store the line number into the parser state (offset +0x3C of the buffer)
    *(int*)(parserBuffer[0] + 0x3C) = lineNumber;
    
    // Expect '('
    if (*(int*)((char*)this + 0x0C) == TOKEN_OPEN_PAREN) {
        // Consume the open parenthesis
        int* sentinel = (int*)TOKEN_INVALID; // 0x11F used as sentinel for "no lookahead"
        *(int*)((char*)this + 0x08) = *(int*)((char*)this + 0x04); // push current token? 
        
        // Advance to next token
        if (*(int*)((char*)this + 0x14) == TOKEN_INVALID) {
            // No peeked token; fetch new one
            int newToken = getNextToken((int*)((char*)this + 0x10));
            *(int*)((char*)this + 0x0C) = newToken;
        } else {
            // Shift from peek slots
            *(int*)((char*)this + 0x0C) = *(int*)((char*)this + 0x14);
            *(int*)((char*)this + 0x10) = *(int*)((char*)this + 0x18);
            *(int*)((char*)this + 0x14) = TOKEN_INVALID;
        }
        
        // If parseNested is set, parse a nested block (e.g., inner function call)
        if (parseNested != 0) {
            parseNestedBlock();
        }
        
        // Parse the content between parentheses (likely arguments/expressions)
        parseSomethingAfterOpenParen();
        
        // Expect ')'
        if (*(int*)((char*)this + 0x0C) == TOKEN_CLOSE_PAREN) {
            // Consume close parenthesis
            *(int*)((char*)this + 0x08) = *(int*)((char*)this + 0x04);
            
            if (*(int*)((char*)this + 0x14) == TOKEN_INVALID) {
                int newToken = getNextToken((int*)((char*)this + 0x10));
                *(int*)((char*)this + 0x0C) = newToken;
            } else {
                *(int*)((char*)this + 0x0C) = *(int*)((char*)this + 0x14);
                *(int*)((char*)this + 0x10) = *(int*)((char*)this + 0x18);
                *(int*)((char*)this + 0x14) = TOKEN_INVALID;
            }
            
            // Now expect statement end (0x106, e.g., ';' or 'then')
            while (true) {
                advanceLexer();
                if (*(int*)((char*)this + 0x0C) == TOKEN_STATEMENT_END) break;
                
                // Error case: expected statement end, but found something else
                if (lineNumber == *(int*)((char*)this + 0x04)) {
                    // Simple error: "`<expected>' expected"
                    int err = reportError("`%s' expected", ")"); // placeholder; actual PTR_DAT_00e2a8d4
                } else {
                    // Complex error: "`<expected>' expected (to close `<function>' at line <line>)"
                    int err = reportError("`%s' expected (to close `%s' at line %d)",
                                          ")",              // PTR_DAT_00e2a8d4
                                          "function",       // PTR_s_function_00e2a8e0
                                          lineNumber);
                }
            }
            
            // Finalize and clean up
            finalizeParseAfterCloseParen();
            cleanupParserState(parserBuffer);
            return;
        } else {
            // Error: expected ')' after the expression
            int err = reportError("`%s' expected", ")");
            // The error reporting then loops? (original code goes to error label)
        }
    } else {
        // Error: expected '(' at start
        int err = reportError("`%s' expected", "(");
    }
    
    // Error path: report the missing symbol and then (in original) some error reporting call
    // The original code jumps to a common error reporting sequence using FUN_00638b80
    // We simplify by just reporting and aborting.
}