// FUNC_NAME: PatternMatcher::matchPattern
int PatternMatcher::matchPattern(int thisPtr, char *patternStart, char *inputStr, int recursionDepth)
{
    char inputChar;
    uint matchResult;
    int recursiveResult;
    int matchPos;
    char *patternPos;

    matchPos = 0;
    patternPos = patternStart;
    // Loop while patternPos is within the pattern buffer (end pointer at thisPtr+4)
    if (patternStart < *(char **)(thisPtr + 4)) {
        do {
            inputChar = *inputStr;
            if (inputChar == '%') {
                // % wildcard: expects any number of characters (including zero)
                matchResult = FUN_0062b830();  // handlePercentWildcard
LAB_0062bafc:
                if (matchResult == 0) break;
            }
            else if (inputChar != '.') {
                if (inputChar == '[') {
                    // Character class like [abc]
                    matchResult = FUN_0062b940(*patternPos, recursionDepth - 1);  // handleCharacterClass
                }
                else {
                    // Literal character match
                    matchResult = (uint)(inputChar == *patternPos);
                }
                goto LAB_0062bafc;
            }
            // '.' matches any single character (no explicit action, just advance)
            patternPos = patternPos + 1;
            matchPos = matchPos + 1;
        } while (patternPos < *(char **)(thisPtr + 4));
        if (matchPos < 0) {
            return 0;
        }
    }
    // Backtracking: try shorter matches by moving pattern start backwards
    do {
        recursiveResult = FUN_0062bd60(thisPtr, patternStart + matchPos, recursionDepth + 1);
        if (recursiveResult != 0) {
            return recursiveResult;
        }
        matchPos = matchPos - 1;
    } while (-1 < matchPos);
    return 0;
}