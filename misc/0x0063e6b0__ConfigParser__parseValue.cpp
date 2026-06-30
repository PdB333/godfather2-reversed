// FUNC_NAME: ConfigParser::parseValue

#define TOKEN_EOF 0x11f

int __thiscall ConfigParser::parseValue(ConfigParser* this, void* context) {
    struct Token {
        char header[4];       // +0x00: local_614[4]
        int field1;           // +0x04: local_610
        int field2;           // +0x08: local_60c
        int value;            // +0x0C: local_608
        int valueStr;         // +0x10: local_604
        int type;             // +0x14: local_600
        int savedValue;       // +0x18: local_5fc
        int zeroField;        // +0x1C: local_5e4
        int returnValue;      // +0x20: local_5e0
    };

    // Get pointer to input buffer (stored at +0x10 in "this")
    char* inputString = *(char**)((uint)this + 0x10);

    // Calculate string length (strlen)
    char* p = inputString;
    while (*p != '\0')
        p++;
    int length = p - inputString;

    // Parse the entire input as a string token
    int tokenResult = parseInputString(context, inputString, length);

    // Skip whitespace after parsing
    advanceLexer(tokenResult);

    // Initialize token structure
    Token token;
    initToken(&token);

    // Copy field1 -> field2 (likely copying a token ID or data)
    token.field2 = token.field1;

    // Check if current token type is EOF
    if (token.type == TOKEN_EOF) {
        // Parse an integer value from the saved string
        token.value = parseInteger(&token.valueStr);
    } else {
        // Save current type and value, then set type to EOF
        int savedType = token.type;
        int savedStr = token.savedValue;
        token.value = savedType;
        token.valueStr = savedStr;
        token.type = TOKEN_EOF;
    }

    // Finalize token parsing
    finalizeToken(&token);

    // If the computed value is not EOF, it's an error
    if (token.value != TOKEN_EOF) {
        errorHandler("<eof> expected");
    }

    // Clean up token resources
    destroyToken(&token);

    return token.returnValue;
}