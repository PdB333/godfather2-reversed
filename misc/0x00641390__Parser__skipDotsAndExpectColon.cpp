//FUNC_NAME: Parser::skipDotsAndExpectColon
// Address: 0x00641390
// Role: Skips consecutive '.' characters, then expects and consumes a ':' character.
// Returns true if colon found, false otherwise.

#include <cstdint>

class Parser {
public:
    // +0x0c: current character (int)
    // +0x1c: pointer to output buffer or token storage
    int32_t currentChar;          // offset 0x0c
    void* tokenBuffer;            // offset 0x1c

    // __thiscall member functions (declared here for clarity)
    int32_t getNextChar();        // FUN_0063dd40
    void appendChar(void* buffer, int32_t ch); // FUN_0063e160
    void advance();               // FUN_0063e790

    // Main function
    bool skipDotsAndExpectColon() {
        int32_t ch = getNextChar();
        appendChar(tokenBuffer, ch);

        // Skip all consecutive dots
        while (currentChar == '.') {
            advance();
            // After advance, currentChar is updated; no need to re-read
        }

        // Expect a colon
        if (currentChar != ':') {
            return false;
        }

        // Consume the colon
        advance();
        return true;
    }
};