// FUNC_NAME: StringParser::findMatchingBracket
// Address: 0x0062ba30
// Role: Find the matching closing bracket for a two-character bracket pattern (open, close) in a buffer.
// The buffer is bounded by m_bufferEnd (offset +0x04 from this pointer stored in EDI).
// Returns pointer to character after the matching close bracket, or nullptr if not found.
// Calls logError if pattern is unbalanced (open or close char missing).

#include <cstddef>

// Forward declaration of error function
void logError(const char* message);

class StringParser {
public:
    const char* m_bufferEnd; // +0x04: pointer to end of buffer (one past last valid char)

    // __fastcall: first param (cursor) in EAX, second param (pattern) in EDX, this in EDI.
    char* __fastcall findMatchingBracket(const char* cursor, const char* pattern);
};

char* __fastcall StringParser::findMatchingBracket(const char* cursor, const char* pattern)
{
    char openChar = pattern[0];
    char closeChar = pattern[1];

    // Pattern must have both open and close characters
    if (openChar == '\0' || closeChar == '\0') {
        logError("unbalanced pattern");
        // Trigger breakpoint or crash (orig: swi 3)
        __debugbreak(); // software interrupt
        return nullptr;
    }

    // Check if current character matches the opening bracket
    if (*cursor == openChar) {
        int depth = 1;
        cursor++; // move past the opening bracket

        // Iterate through buffer until end
        while (cursor < m_bufferEnd) {
            if (*cursor == closeChar) {
                depth--;
                if (depth == 0) {
                    // Return pointer to character after the matching close bracket
                    return const_cast<char*>(cursor + 1);
                }
            } else if (*cursor == openChar) {
                depth++;
            }
            cursor++;
        }
        // Reached end without matching close bracket
        return nullptr;
    }
    // No opening bracket at current position
    return nullptr;
}