// FUNC_NAME: Parser::expectCloseToken
// Address: 0x0063dc80
// Description: Expects a closing token to match an opening token. Handles state machine for nested structures.
// Parameters: this (ecx), currentToken (eax), expectedCloseToken (edi), lineNumber (stack param2)

class Parser {
public:
    int m_expectedCloseToken; // +0x04
    int m_savedToken;         // +0x08
    int m_currentToken;       // +0x0C
    int m_stateStackTop;      // +0x10 (pointer to stack of states)
    int m_openToken;          // +0x14
    int m_openTokenLine;      // +0x18

    static const int TOKEN_EOF = 0x11f; // 287

    void expectCloseToken(int currentToken, int expectedCloseToken, int lineNumber) {
        if (m_currentToken != expectedCloseToken) {
            // Current token does not match the expected close token
            if (lineNumber == m_expectedCloseToken) {
                // Special case: use line number as close token
                handleCloseMatch();
                return;
            }

            // Report error
            const char* expectedName = (currentToken < 0x101) 
                ? GetTokenName(&TOKEN_TABLE) 
                : GetTokenNameByIndex(currentToken);
            const char* openingName = (expectedCloseToken < 0x101) 
                ? GetTokenName(&TOKEN_TABLE) 
                : GetTokenNameByIndex(expectedCloseToken);
            ReportError("`%s' expected (to close `%s' at line %d)", expectedName, openingName, lineNumber);
            raiseDebugBreak();
            // Unreachable
            return;
        }

        // Token matched, proceed with state machine
        m_savedToken = m_expectedCloseToken;
        if (m_openToken != TOKEN_EOF) {
            m_currentToken = m_openToken;
            m_stateStackTop = m_openTokenLine;
            m_openToken = TOKEN_EOF;
            return;
        }

        m_currentToken = popState(); // pop from stack at +0x10
    }

private:
    void handleCloseMatch(); // FUN_0063dbb0
    const char* GetTokenName(int table); // FUN_00636c00
    const char* GetTokenNameByIndex(int index); // DAT_00e2a4bc[index]
    void ReportError(const char* fmt, ...); // FUN_00638b80
    int popState(); // FUN_00639c70(&m_stateStackTop)
    void raiseDebugBreak(); // assembly int3
};

extern int TOKEN_TABLE; // DAT_00e4242c