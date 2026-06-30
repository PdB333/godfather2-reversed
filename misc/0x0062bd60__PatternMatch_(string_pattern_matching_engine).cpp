// FUNC_NAME: PatternMatch (string pattern matching engine)
// Address: 0x0062bd60
// Role: Recursive pattern matcher for string scanning with support for wildcards (*, +, ?, .), character classes ([]), digit patterns (%d), boundary (%b), field patterns (%f), and grouping parentheses.
// The context struct holds start and end pointers into the input string.
// Returns pointer to matched position in input string, or NULL on failure.

struct MatchContext {
    char* start; // +0x00
    char* end;   // +0x04
};

extern char* FUN_0062b7d0();              // Helper: presumably advances pattern past a special token
extern char* FUN_0062b830();              // Helper: for '.' wildcard match
extern char* FUN_0062b940(char c, char* pattern); // Character class match ('[')
extern char* FUN_0062ba30();              // Handle '%b' (backspace?)
extern char* FUN_0062baa0(MatchContext*, char* input, char* pattern, char* p); // Handle '*'
extern char* FUN_0062bb40(MatchContext*, char* pattern, char* p); // Handle '-'
extern char* FUN_0062bbd0(char* pattern, int op); // Handle '('
extern char* FUN_0062bc20(char* pattern); // Handle ')'
extern char* FUN_0062bc80(char* input);   // Handle '%d' (digit)
extern void FUN_00627bd0(const char* msg); // Error message

char* PatternMatch(MatchContext* ctx, char* input, char* pattern) {
  do {
    switch (*pattern) {
    case '\0':
      // End of pattern - return current position (success)
      return input;

    case '$':
      // End-of-string anchor
      if (pattern[1] == '\0') {
        // If input is at end, return input pointer; otherwise return NULL (via bit hack)
        return (char*)((input != ctx->end) - 1 & (uint)input);
      }
      // Otherwise fall through to default

    default:
switchD_0062bd83_caseD_1:
      {
        // Save a copy of pattern position for recursion/error handling
        char* savedPattern = FUN_0062b7d0();

        // Check if we are within input bounds
        bool withinBounds = input < ctx->end;

        if (withinBounds) {
          char currentPattern = *pattern;
          uint matchResult;

          if (currentPattern == '%') {
            // Handle percent escapes - already handled above but fallback
            matchResult = FUN_0062b830();
            goto LAB_0062beae;
          } else if (currentPattern != '.') {
            if (currentPattern == '[') {
              // Character class
              matchResult = FUN_0062b940(*input, savedPattern - 1);
            } else {
              // Literal character match
              matchResult = (uint)(currentPattern == *input);
            }
            goto LAB_0062beae;
          }

          // '.' matches any character
          matchResult = true;
        } else {
LAB_0062bebc:
          matchResult = false;
        }

        // Based on saved pattern's first character, decide next action
        switch (*savedPattern) {
        case '*':
          // Match zero or more of the current pattern element
          return FUN_0062baa0(ctx, input, pattern, savedPattern);
        case '+':
          // Match one or more
          if (!matchResult) {
            return nullptr;
          }
          return FUN_0062baa0(ctx, input + 1, pattern, savedPattern);
        default:
          // Normal sequential match - advance both pointers
          if (!matchResult) {
            return nullptr;
          }
          input = input + 1;
          pattern = savedPattern;
          break;
        case '-':
          // Skip pattern (negative lookahead?)
          return FUN_0062bb40(ctx, pattern, savedPattern);
        case '?':
          // Optional match: try skipping the pattern element
          if (matchResult) {
            char* result = PatternMatch(ctx, input + 1, savedPattern + 1);
            if (result != nullptr) {
              return result;
            }
          }
          // Fall through: try matching without consuming input, advancing pattern to after '?'
          pattern = savedPattern + 1;
        }
      }
      break;

    case '%':
      // Percent-prefixed pattern elements
      {
        byte nextChar = pattern[1];
        if (nextChar == 0x62) {
          // '%b' - boundary? Possibly word boundary or backspace
          input = FUN_0062ba30();
          if (input == nullptr) {
            return nullptr;
          }
          pattern = pattern + 4; // skip over '%b' and any extra characters (likely 2-digit offset?)
        } else if (nextChar == 0x66) {
          // '%f' - field pattern
          if (pattern[2] != '[') {
            FUN_00627bd0("missing `[' after `%%f' in pattern");
            return input;
          }
          char* saved = FUN_0062b7d0();
          char prevChar;
          if (input == ctx->start) {
            prevChar = '\0';
          } else {
            prevChar = input[-1];
          }
          int result = FUN_0062b940(prevChar, saved - 1);
          if (result != 0) {
            return nullptr;
          }
          result = FUN_0062b940(*input, saved - 1);
          if (result == 0) {
            return nullptr;
          }
          // Continue matching (pattern advances implicitly via saved?)
        } else {
          int isDigit = _isdigit((uint)nextChar);
          if (isDigit == 0) {
            // Not a digit escape - treat as literal '%' and fall back
            goto switchD_0062bd83_caseD_1;
          }
          // '%' followed by digit: skip that many characters or match digit
          input = FUN_0062bc80(input);
          if (input == nullptr) {
            return nullptr;
          }
          pattern = pattern + 2; // skip '%d'
        }
      }
      break;

    case '(':
      // Start of group
      if (pattern[1] == ')') {
        // Empty group
        return FUN_0062bbd0(pattern + 2, 0xfffffffe);
      }
      return FUN_0062bbd0(pattern + 1, 0xffffffff);

    case ')':
      // End of group
      return FUN_0062bc20(pattern + 1);
    }
  } while (true);
}