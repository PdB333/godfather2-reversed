// FUNC_NAME: PatternMatcher::matchGlob
// Function address: 0x0062baa0
// This function implements a glob-style pattern matching algorithm.
// It matches string 'str' (bounded by m_strEnd) against pattern 'pattern'.
// Wildcards: '%' matches any string (like *), '.' matches any single character (like ?),
// and '[' introduces a character class.
// The algorithm uses recursive backtracking via a helper function (matchRecursiveBacktrack).
// param_4 appears to be a depth limit or recursion counter.

#include <cstdint>

class PatternMatcher {
public:
    char* m_strEnd; // offset +0x04: end pointer for the string to match

    // Helper functions (implemented elsewhere)
    int matchWildcard();                     // FUN_0062b830
    int matchCharClass(char c, int depth);   // FUN_0062b940
    int matchRecursiveBacktrack(char* pos, int depth); // FUN_0062bd60

    // Main glob matcher
    // Returns non-zero on match, 0 on failure.
    int matchGlob(char* str, char* pattern, int depth) {
        int matchedCount = 0;
        char* pStr = str; // current position in string

        // Advance through pattern and string simultaneously
        if (str < m_strEnd) {
            do {
                char patternChar = *pattern;

                if (patternChar == '%') {
                    // Wildcard: match any remaining string
                    uint result = matchWildcard();
                    if (result == 0) {
                        // If wildcard fails, break out of the loop
                        break;
                    }
                }
                else if (patternChar != '.') {
                    // Not a '.' (single char wildcard)
                    if (patternChar == '[') {
                        // Character class: check if current string char matches class
                        uint result = matchCharClass(*pStr, depth - 1);
                        if (result == 0) {
                            break;
                        }
                    }
                    else {
                        // Literal character comparison
                        uint result = (uint)(patternChar == *pStr);
                        if (result == 0) {
                            break;
                        }
                    }
                }
                // If patternChar == '.', just skip the character (match any single char)

                pStr++;
                matchedCount++;
            } while (pStr < m_strEnd);
        }

        // If no characters were matched, return failure
        if (matchedCount < 0) {
            return 0;
        }

        // Attempt backtracking: try to match with fewer consumed characters
        do {
            int result = matchRecursiveBacktrack(str + matchedCount, depth + 1);
            if (result != 0) {
                return result;
            }
            matchedCount--;
        } while (matchedCount >= 0);

        return 0;
    }
};