// FUNC_NAME: nextToken
char* nextToken(char* str, int stopOnNewline, bool* escapeFlag)
{
    bool singleQuote = false;
    bool doubleQuote = false;

    if (escapeFlag != nullptr)
    {
        *escapeFlag = false;
    }

    char firstChar = *str;
    if (firstChar == '\0')
    {
        return str;
    }

    if (firstChar == '\"')
    {
        doubleQuote = true;
    }
    else if (firstChar == '\'')
    {
        singleQuote = true;
    }

    char* pos = str;
    while (true)
    {
        char* cur = pos;
        char c = *cur;

        // Handle newline and line counting
        if (c == '\n')
        {
            if (stopOnNewline != 0)
            {
                return cur;
            }
            g_lineNumber++;  // DAT_01164078
        }

        // Check delimiter set (global, e.g. s_delimiterChars)
        if ((str < cur) && (g_delimiterChars != nullptr))
        {
            char* d = g_delimiterChars;
            while (*d != '\0')
            {
                if (*cur == *d)
                {
                    if (!singleQuote && !doubleQuote)
                    {
                        return cur;
                    }
                    break; // inside a quote, skip delimiter check
                }
                d++;
            }
        }

        // Look at next character
        char nextChar = *(cur + 1);
        if (nextChar == '\0')
        {
            return cur + 1; // end of string
        }

        if (doubleQuote)
        {
            // Inside double quotes
            if (nextChar == '\\')
            {
                if (*(cur + 2) == '\"')
                {
                    if (escapeFlag != nullptr)
                    {
                        *escapeFlag = true;
                    }
                    pos = cur + 2; // skip escaped quote
                    continue;
                }
            }
            if (nextChar == '\"')
            {
                // End of double-quoted string
                pos = cur + 2;
                break;
            }
        }
        else if (singleQuote)
        {
            // Inside single quotes
            if (nextChar == '\\')
            {
                if (*(cur + 2) == '\'')
                {
                    if (escapeFlag != nullptr)
                    {
                        *escapeFlag = true;
                    }
                    pos = cur + 2;
                    continue;
                }
            }
            if (nextChar == '\'')
            {
                // End of single-quoted string
                pos = cur + 2;
                break;
            }
        }
        else
        {
            // Not inside quotes
            // Check for start of a quote
            if (nextChar == '\"')
            {
                doubleQuote = true;
                // Re-check delimiter set inside quotes? The code does a check again if delimiter set exists
                if ((g_delimiterChars != nullptr) && (*g_delimiterChars != '\0'))
                {
                    char* d = g_delimiterChars;
                    while (*d != '\0')
                    {
                        if (*cur == *d)
                        {
                            return cur + 1; // return after the delimiter? Actually returns cur+1? Wait code: "return pcVar4;" which is cur+1.
                        }
                        d++;
                    }
                }
                pos = cur + 1;
                continue;
            }
            // Check for whitespace / comments / delimiters
            if ((nextChar == ' ') || (nextChar == '\t') || (nextChar == '\r') || (nextChar == '\n'))
            {
                return cur + 1;
            }
            // C++ style comments: // or /*
            if (*str == '/')
            {
                if (*(str + 1) == '/')
                {
                    return cur + 1;
                }
                if (*(str + 1) == '*')
                {
                    return cur + 1;
                }
            }
            // Check delimiter set again (same as above but different branch)
            if ((g_delimiterChars != nullptr) && (*g_delimiterChars != '\0'))
            {
                char* d = g_delimiterChars;
                while (*d != '\0')
                {
                    if (*cur == *d)
                    {
                        return cur + 1;
                    }
                    d++;
                }
            }
        }

        pos = cur + 1; // advance to next character
    }

    return pos; // after closing quote
}