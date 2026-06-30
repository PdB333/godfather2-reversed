// FUNC_NAME: ScriptParser::parseRepeatStatement

class ScriptParser {
public:
    // Offset +0x04: current token type (int)
    // Offset +0x08: previous token type (int)
    // Offset +0x0c: lookahead token type (int)
    // Offset +0x10: lookahead token value (int)
    // Offset +0x14: lookahead token line (int)
    // Offset +0x18: current token value (int)
    // Offset +0x1c: pointer to LexerState

    class LexerState {
    public:
        // +0x14: token value (int)
        // +0x18: current line number (int)
        // +0x1c: saved line number (int)
        // +0x34: token type (int)
    };

    // Token structure (temporary on stack)
    struct Token {
        int type;       // +0x00
        int value;      // +0x04
        int line;       // +0x08
        int flag0;      // +0x0c
        int flag1;      // +0x10
        int unknown2;   // +0x14
        int unknown3;   // +0x18
        int unknown4;   // +0x1c
        int unknown5;   // +0x20
        int unknown6;   // +0x24
        int errorFlag;  // +0x28
    };

    void __thiscall parseRepeatStatement(int repeatLine);

private:
    // Helper methods (inferred from callee names)
    int  __thiscall getNextToken(void* tokenOut);                    // FUN_00639c70
    void __thiscall parseStatementList();                            // FUN_006417c0
    void __thiscall parseEndOfStatement();                           // FUN_0063e400
    void __thiscall parseCondition();                                // FUN_0063fad0
    void __thiscall maybeParseSemicolon();                           // FUN_00643310
    void __thiscall advanceLexer(LexerState* lexer);                 // FUN_00642880
    void __thiscall insertMissingTokens(LexerState* lexer, int line, int token, int, int, int); // FUN_006426a0
    void error(const char* fmt, ...);                                // via FUN_00636c00 + FUN_00638b80
};

void ScriptParser::parseRepeatStatement(int repeatLine) {
    LexerState* lexer = m_lexer;
    int bodyStartLine = lexer->m_lineNumber;           // +0x18
    lexer->m_savedLine = bodyStartLine;                 // +0x1c

    // Build a temporary token on stack for the body start (this acts as a token insertion)
    Token bodyToken;
    bodyToken.type = -1;                                // local_40
    bodyToken.flag1 = 1;                                // local_34
    bodyToken.line = lexer->m_tokenType;                // +0x34 → local_3c
    bodyToken.flag0 = 0;                                // local_38
    bodyToken.value = lexer->m_tokenValue;              // +0x14 → local_44
    lexer->m_tokenValue = reinterpret_cast<int>(&bodyToken); // Point lexer to the temp token

    // Shift tokens: previous becomes current, advance lookahead
    m_currentTokenType = m_lookaheadTokenType;          // +0x08 = +0x04

    // If the lookahead is 'repeat' (0x11f), consume it normally
    if (m_lookaheadTokenType == 0x11f) {
        m_currentTokenType = getNextToken(&m_lookaheadTokenValue); // +0x10 → updates +0x0c
    } else {
        // Otherwise manually shift
        m_currentTokenType = m_lookaheadTokenType;      // +0x0c = +0x04
        m_lookaheadTokenValue = m_currentTokenValue;    // +0x10 = +0x18
        m_lookaheadTokenLine = 0x11f;                   // +0x14 = 0x11f
    }

    // Parse the body statements
    parseStatementList();
    parseEndOfStatement();

    // Now we expect the 'until' token (0x114)
    if (m_currentTokenType == 0x114) {
        // Consume 'until'
        m_currentTokenType = m_lookaheadTokenType;      // +0x08 = +0x04
        if (m_lookaheadTokenType == 0x11f) {
            m_currentTokenType = getNextToken(&m_lookaheadTokenValue); // +0x0c
        } else {
            m_currentTokenType = m_lookaheadTokenType;  // +0x0c = +0x04
            m_lookaheadTokenValue = m_currentTokenValue; // +0x10 = +0x18
            m_lookaheadTokenLine = 0x11f;               // +0x14 = 0x11f
        }

        // Parse the condition after 'until'
        parseCondition();

        // Check error flag from temporary token
        if (bodyToken.errorFlag == 1) {
            bodyToken.errorFlag = 3;                    // Mark as error recovered
        }

        // Expect end of condition statement
        maybeParseSemicolon();

        // Clean up lexer
        LexerState* lexerAfter = m_lexer;
        lexerAfter->m_savedLine = lexerAfter->m_lineNumber; // +0x1c = +0x18
        advanceLexer(lexerAfter);

        // If we haven't moved past the body start line, we may need to reparse
        if (bodyStartLine == lexer->m_lineNumber) {
            lexer->m_savedLine = lexer->m_lineNumber;  // +0x1c = +0x18
            advanceLexer(lexer);
            parseEndOfStatement();
            return;
        }
    } else {
        // Error: expected 'until' token
        if (repeatLine == m_currentTokenType) { // param_1 compared to +0x04
            error("`%s' expected", "until");
            repeatLine = reportError();            // FUN_00638b80
        }
        error("`%s' expected (to close `%s' at line %d)", "until", "repeat", repeatLine);
        reportError();

        // Insert missing tokens to recover
        insertMissingTokens(lexer, bodyStartLine, 0xff, bodyStartLine, 0xff, bodyStartLine);
    }

    parseEndOfStatement();
}