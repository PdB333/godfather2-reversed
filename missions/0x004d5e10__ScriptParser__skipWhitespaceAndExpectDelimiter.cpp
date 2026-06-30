// FUNC_NAME: ScriptParser::skipWhitespaceAndExpectDelimiter
void ScriptParser::skipWhitespaceAndExpectDelimiter(char*& pStr, int stopAtNewline, const char* delimiters)
{
    // +0x00 Global line number counter (DAT_01164078)
    gLineNumber = (gLineNumber < 1) ? 1 : gLineNumber;
    char c = *pStr;
    int lineNum = gLineNumber;
    while (c != '\0') {
        if (c == '\n') {
            if (stopAtNewline) {
                return;
            }
            pStr++;
            lineNum++;
            gLineNumber = lineNum;
        } else if ((c != '#') || (gIgnoreHashComments != 0)) {
            // Skip whitespace: spaces, tabs, carriage returns
            if (c == ' ' || c == '\t' || c == '\r') {
                do {
                    gLineNumber = lineNum;
                    c = *pStr;
                    if (c != ' ' && c != '\t' && c != '\r' && c != '\n')
                        goto checkDelimiter;
                    if (c == '\n') {
                        if (stopAtNewline) goto checkDelimiter;
                        lineNum++;
                    }
                    pStr++;
                } while (true);
            }
            // Handle line comments '//'
            if (c == '/') {
                if (pStr[1] == '/') {
                    do {
                        if (c == '\n') break;
                        c = pStr[1];
                        pStr++;
                    } while (c != '\0');
                    if (stopAtNewline && *pStr == '\n') goto checkDelimiter;
                } else if (pStr[1] == '*') {
                    // Block comment '/* ... */'
                    char next = '/';
                    do {
                        if (pStr[-1] == '*' && next == '/') break;
                        next = pStr[1];
                        pStr++;
                        if (next == '\0') return;
                    } while (true);
                } else {
                    goto expectDelimiter;
                }
                if (*pStr == '\0') {
                    return;
                }
            } else {
expectDelimiter:
                // Expect current character to be one of the delimiter tokens
                if (delimiters == nullptr) {
                    return;
                }
                if (*delimiters == '\0') {
                    return;
                }
                const char* delimPtr = delimiters;
                while (*delimPtr != '\0') {
                    if (c == *delimPtr) break;
                    delimPtr++;
                    if (*delimPtr == '\0') return;
                }
            }
            pStr++;
        }
checkDelimiter:
        c = *pStr;
    }
}