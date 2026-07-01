// FUNC_NAME: CommandParser::parseCCommand
int __thiscall CommandParser::parseCCommand(const char* cmd, int* outOffset, int* outId)
{
    // Parse format "[c=...]" where ... is either "RESET" or an identifier
    int result = -1; // 0xffffffff
    *outOffset = 0;

    // Check opening bracket
    if (*cmd != '[')
        return -1;

    // Check 'c' (case-insensitive)
    char c = cmd[1];
    if ((c - 'A') < 0x1a) // uppercase check
        c = c + ' '; // tolower
    if (c != 'c')
        return -1;

    // Check '='
    if (cmd[2] != '=')
        return -1;

    // Extract token after "c="
    // FUN_004d3bc0 likely duplicates the substring
    char* token = (char*)String::duplicate(cmd + 3);

    // Parse token into a structure (lookup in global table at 0x00e337c0)
    TokenNode node[3]; // local_14 is array of 3 ints, but likely a struct with token data and cleanup fn ptrs
    int tokenResult = TokenTable::lookup(node, &globalTokenTable);
    String::free(tokenResult);

    // If we got a token, call its cleanup function? Actually node[0] != 0 triggers call
    if (node[0] != 0) {
        node[2](); // local_8 is a function pointer
    }

    // Check if token equals "RESET"
    int cmp = String::compare("RESET");
    if (cmp == 0) {
        // Token is "RESET" - return success (1)
        result = 1;
    } else {
        // Token is something else - get its ID
        int id = GetCommandId(); // FUN_0049af90
        *outId = id;
        if (id == 0x18) { // Invalid ID (24?)
            // Jump to cleanup without setting result (remains -1)
            goto cleanup;
        }
        result = 0; // Success
    }

    // Set offset from parsed token data
    *outOffset = iStack_20 + 4; // iStack_20 from token parsing

cleanup:
    if (node[1] != 0) {
        node[1](); // pcStack_18 is cleanup function for first token data
    }
    return result;
}