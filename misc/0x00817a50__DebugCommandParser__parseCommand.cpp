// FUNC_NAME: DebugCommandParser::parseCommand
void DebugCommandParser::parseCommand(void* context, CommandBuffer* cmd) {
    char c;
    int tokenResult;
    char* str;

    tokenResult = parseToken(context, cmd);
    str = (char*)getTokenValue(tokenResult, cmd + 4);

    // Skip leading whitespace characters
    while ((c = *str) != '\0') {
        if (c == ' ' || c == '\n' || c == '\t' || c == '\r' || c == '\f' || c == '\v') {
            str++;
        } else {
            break;
        }
    }

    // Check if command starts with "d=" (debug directive)
    if (__strnicmp(str, "d=", 2) == 0) {
        // Advance past "d=" and parse the parameter
        tokenResult = parseToken(str + 2, cmd + 1);
        getTokenValue(tokenResult, cmd + 8);
        return;
    }

    // Unknown command – set default response
    cmd->command = '+';  // +0x01: command type
    cmd->param = 0;      // +0x08: parameter value
}