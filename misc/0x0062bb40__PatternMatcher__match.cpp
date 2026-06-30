// FUNC_NAME: PatternMatcher::match
// Function at 0x0062bb40: glob-like pattern matching with '%' wildcard, '.' literal, '[' character classes.
// This appears to be part of a string matching utility, possibly for console commands or configuration parsing.

struct PatternMatcher {
    char *currentChar; // +0x00: current character pointer
    char *endChar;     // +0x04: end-of-string pointer
};

// Forward declarations for helper functions
extern char* advanceMatch(PatternMatcher *matcher, char *pos, int depth);
extern unsigned int matchCharacterClass(char inputChar, int classLength);
extern unsigned int matchWildcardSequence();

char* PatternMatcher::match(char *pattern, int depth) {
    char *result;
    unsigned int matched;

    result = advanceMatch(this, NULL, depth);  // initial call to get current position
    if (result != 0) {
        return result;
    }

    // Loop through characters in the string buffer
    while (this->currentChar < this->endChar) {
        char patternChar = *pattern;
        if (patternChar == '%') {
            matched = matchWildcardSequence();
        }
        else if (patternChar == '.') {
            matched = matchWildcardSequence();
        }
        else if (patternChar == '[') {
            matched = matchCharacterClass(*this->currentChar, depth - 1);
        }
        else {
            matched = (unsigned int)(patternChar == *this->currentChar);
        }

        if (matched == 0) {
            break;  // no match possible from this position
        }

        this->currentChar++;
        result = advanceMatch(this, this->currentChar, depth + 1);
        if (result != 0) {
            return result;
        }
    }

    return 0;  // no match found
}