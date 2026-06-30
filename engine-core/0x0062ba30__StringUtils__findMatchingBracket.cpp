// FUNC_NAME: StringUtils::findMatchingBracket
// Address: 0x0062ba30
// Role: Finds the matching closing character (e.g., ')' for '(') in a delimited string,
// given a starting position and a two-character pattern (open/close).
// Uses internal end-of-string bounds stored in this object.

class StringUtils {
public:
    // String bounds: offset 0 = m_pBegin, offset 4 = m_pEnd
    char* m_pBegin; // +0x00
    char* m_pEnd;   // +0x04

    // start - pointer to the opening character in the string
    // pattern - two-character string where pattern[0] is the opening char, pattern[1] is the closing
    // Returns pointer to the character after the matching closing character, or nullptr if not found.
    // If pattern is invalid (empty or single character), triggers an error and a debug break.
    char* __fastcall findMatchingBracket(char* start, const char* pattern) {
        char openChar = pattern[0];
        if (openChar != '\0' && pattern[1] != '\0') {
            if (*start == openChar) {
                int depth = 1;
                char* p = start + 1;
                // Scan within the string's buffer bounds
                while (p < m_pEnd) {
                    if (*p == pattern[1]) {
                        depth--;
                        if (depth == 0) {
                            return p + 1; // point after closing character
                        }
                    } else if (*p == openChar) {
                        depth++;
                    }
                    p++;
                }
                return nullptr; // unbalanced
            }
            return nullptr; // start doesn't match opening char
        }
        // Invalid pattern
        FUN_00627bd0("unbalanced pattern");
        __debugbreak(); // swi(3) software interrupt
        return nullptr;
    }
};