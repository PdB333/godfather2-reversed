// FUNC_NAME: PatternMatcher::matchInternal
// Address: 0x0062bd60
// Role: Recursive pattern matching engine for simplified regex (supports ., *, +, ?, [, ], $, %, (, ), -, etc.)

struct PatternContext {
    char* m_start; // +0x00: Beginning of input string
    char* m_end;   // +0x04: One past end of input string
};

// External helpers (declared elsewhere)
extern char* parsePatternElement();                 // FUN_0062b7d0 - parse pattern element, return pointer past it
extern uint matchAnyChar();                         // FUN_0062b830 - match any char (for '%' or '.'?)
extern int matchCharClass(char ch, char* classSpec); // FUN_0062b940 - match character against [is class]
extern char* matchRepetition(PatternContext* ctx, char* input, char* pattern, char* afterElem); // FUN_0062baa0 - handle * and +
extern char* matchOptional(PatternContext* ctx, char* pattern, char* afterElem); // FUN_0062bb40 - handle ? and -
extern char* matchGroup(PatternContext* ctx, char* pattern, int mode); // FUN_0062bbd0 - handle ( ... )
extern char* matchEndGroup(PatternContext* ctx, char* pattern);        // FUN_0062bc20 - handle ')' returning next
extern char* matchDigits(char* input);                                  // FUN_0062bc80 - handle %d
extern char* matchBinary(PatternContext* ctx);                          // FUN_0062ba30 - handle %b
extern void errorReport(const char* msg);                              // FUN_00627bd0 - report error

char* PatternMatcher::matchInternal(PatternContext* ctx, char* input, char* pattern) {
    while (true) {
        switch (*pattern) {
        case '\0': // End of pattern -> success, return current input position
            return input;

        case '$': // End anchor
            if (pattern[1] == '\0') {
                // If we're at end of input, return input; else return null (as (input != end)-1 & input)
                bool atEnd = (input != ctx->m_end);
                return (char*)((atEnd - 1) & (uintptr_t)input);
            }
            // Fall through to default (if '$' not at end, treat as literal)
            goto default_case;

        case '%': // Special sequences
        {
            char spec = pattern[1];
            if (spec == 'b') { // %b: match binary? (e.g., 4 bytes)
                input = matchBinary(ctx);
                if (input == nullptr) return nullptr;
                pattern += 4; // skip %b and 2 bytes? Actually pattern[3] probably
                break;
            }
            else if (spec == 'f') { // %f: match format flag? (e.g., %f[...])
                if (pattern[2] != '[') {
                    errorReport("missing `[' after `%f' in pattern");
                    return input;
                }
                char* classSpec = parsePatternElement(); // points to '[' ... ']'
                char chBefore = (input == ctx->m_start) ? '\0' : input[-1];
                if (matchCharClass(chBefore, classSpec - 1) != 0) { // lookback char must not match
                    return nullptr;
                }
                if (matchCharClass(*input, classSpec - 1) == 0) { // current char must match
                    return nullptr;
                }
                // Don't advance input or pattern; pattern advances after %f[...]
                pattern = classSpec; // parsePatternElement returns ptr after ']'?
                break;
            }
            else if (isdigit((unsigned char)spec)) { // %digit: match specific number of chars?
                input = matchDigits(input);
                if (input == nullptr) return nullptr;
                pattern += 2; // skip % and digit
                break;
            }
            else {
                goto default_case; // Treat % as literal char
            }
        }

        case '(': // Group start
        {
            char* afterGroup;
            if (pattern[1] == ')') {
                // Empty group? Return remaining pattern from after "()" with mode 0xfffffffe
                afterGroup = matchGroup(pattern + 2, 0xfffffffe);
            } else {
                afterGroup = matchGroup(pattern + 1, 0xffffffff);
            }
            return afterGroup;
        }

        case ')': // Group end (should not occur at top level)
        {
            char* afterEnd = matchEndGroup(pattern + 1);
            return afterEnd;
        }

        default:
        default_case:
        {
            char* afterElem = parsePatternElement(); // Get pointer past current pattern element (could be char, class, etc.)
            bool charMatched = false;
            if (input < ctx->m_end) {
                char c = *pattern;
                uint matched = 0;
                if (c == '%') {
                    matched = matchAnyChar(); // % matches anything?
                    goto check_match;
                }
                else if (c == '.') {
                    matched = matchAnyChar();
                }
                else if (c == '[') {
                    matched = matchCharClass(*input, afterElem - 1);
                }
                else {
                    matched = (uint)(c == *input);
                }
            check_match:
                if (matched != 0) {
                    charMatched = true;
                }
            }

            switch (*afterElem) {
            case '*': // Zero or more
                return matchRepetition(ctx, input, pattern, afterElem);

            case '+': // One or more
                if (!charMatched) return nullptr;
                return matchRepetition(ctx, input + 1, pattern, afterElem);

            case '-': // Maybe optional (different from ?)
                return matchOptional(ctx, pattern, afterElem);

            case '?': // Zero or one
                if (charMatched) {
                    char* res = matchInternal(ctx, input + 1, afterElem + 1);
                    if (res != nullptr) return res;
                }
                pattern = afterElem + 1; // skip '?' and try without
                break;

            default: // Literal or class - must match exactly one
                if (!charMatched) return nullptr;
                input = input + 1;
                pattern = afterElem; // advance pattern past matched element
                break;
            }
            break;
        }
        }
    }
}