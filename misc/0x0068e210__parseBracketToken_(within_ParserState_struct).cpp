// FUNC_NAME: parseBracketToken (within ParserState struct)
// Address: 0x0068e210
// Parses string for bracketed tokens, skipping "c=" markers and handling "b=" prefix.
// Returns offset high bits with low byte 1 on token found, or 0 if no token.

typedef struct {
    char* currentPos;      // +0x04: current parse pointer
    int baseOffset;        // +0x08: base offset for relative addressing
    int baseLimit;         // +0x0C: some boundary value
    char* tokenStart;      // +0x10: start of extracted token (adjusted)
    int tokenLength;       // +0x14: length of token
    char* bufferStart;     // +0x18: start of entire string buffer
    int bufferSize;        // +0x1C: size of buffer
    int offset;            // +0x20: difference between currentPos and bufferStart
    int remaining;         // +0x24: remaining length to process
} ParserState;

uint __fastcall parseBracketToken(ParserState* state)
{
    char* current;
    char* openBracket;
    char* closeBracket;
    char* prefixStart;
    int iVar5;
    int diff;

    current = state->currentPos;
    prefixStart = NULL;

    if (current == NULL) {
        return 0;
    }

    do {
        openBracket = _strchr(current, '[');
        if (openBracket == NULL) {
            closeBracket = NULL;
            break;
        }
        closeBracket = _strchr(openBracket, ']');
        if (closeBracket == NULL) {
            break;
        }
        // Check if bracket content starts with "c="; if so, skip and continue
        if (__strnicmp(openBracket + 1, "c=", 2) == 0) {
            current = closeBracket + 1;
        } else {
            // Found a non-"c=" bracket, exit loop
            break;
        }
    } while (current != NULL);

    if (closeBracket == NULL) {
        // No valid bracket pair found: set remaining info and return with low byte 0
        diff = state->currentPos - state->bufferStart;
        state->offset = diff;
        state->remaining = state->bufferSize - diff;
        return diff & 0xFFFFFF00;
    }

    // Now handle the found bracket (content does NOT start with "c=")
    if (__strnicmp(openBracket + 1, "b=", 2) == 0) {
        // Skip "b=" prefix
        prefixStart = openBracket + 2;
    } else {
        // No "b=" prefix, prefixStart remains at start of bracket content
        prefixStart = openBracket;
    }

    // Adjust tokenStart using baseOffset
    state->tokenStart = prefixStart + (1 - state->baseOffset);

    // Compute token length (from prefixStart to just before ']')
    iVar5 = (int)(closeBracket - 1) - (int)prefixStart;
    if (iVar5 < 0) {
        state->tokenLength = state->baseLimit - (int)(prefixStart + (1 - state->baseOffset));
    } else {
        state->tokenLength = iVar5;
    }

    // Compute offsets relative to current position
    iVar5 = (int)openBracket - (int)state->currentPos;
    diff = state->currentPos - state->bufferStart;
    state->offset = diff;

    if (iVar5 < 0) {
        state->remaining = state->bufferSize - diff;
    } else {
        state->remaining = iVar5;
    }

    // Move currentPos past the closing bracket
    state->currentPos = closeBracket + 1;

    // Return offset high bits with low byte set to 1
    return (diff & 0xFFFFFF00) | 1;
}