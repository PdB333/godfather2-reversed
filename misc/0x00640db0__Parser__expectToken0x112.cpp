// FUNC_NAME: Parser::expectToken0x112
// Address: 0x00640db0
// This function reads the next token from the parser stream and expects it to be token 0x112 (likely ')' or similar closing token).
// If the token matches, it performs stack manipulation and finalization; otherwise it triggers a fatal error.

#include <cstdint>

// Forward declarations of called functions (from EA EARS engine)
int32_t __fastcall Parser::readNextToken(ParserState* parser); // FUN_00639c70
int32_t __fastcall Parser::consumeToken(ParserState* parser); // FUN_0063fad0
void __fastcall Parser::updateParseStack(); // FUN_00643310
void __fastcall Parser::resetSubparser(ParserState* sub); // FUN_00642880
void __fastcall Parser::executeFinalAction(ParserState* parser); // FUN_006417c0
void __fastcall Parser::finalizeParse(); // FUN_0063e400
void __fastcall errorPrintf(const char* format, ...); // FUN_00636c00
void __fastcall errorAbort(); // FUN_00638b80

// Structure representing the parser state
struct ParserState {
    // +0x00: unknown (possibly vtable pointer?)
    // +0x04: some backup token?
    int32_t unknown4;
    // +0x08: token backup
    int32_t tokenBackup;
    // +0x0c: current token read
    int32_t currentToken;
    // +0x10: next token buffer
    int32_t nextTokenBuffer;
    // +0x14: lookahead token type (0x11f means EOF/no token)
    int32_t lookaheadTokenType;
    // +0x18: further lookahead token
    int32_t furtherLookaheadToken;
    // +0x1c: pointer to child/other parse state
    ParserState* childState;
};

// External token constants
const int32_t TOKEN_EOF = 0x11f;       // end-of-file token
const int32_t EXPECTED_TOKEN = 0x112;  // expected token (e.g., closing bracket)

void __fastcall Parser::expectToken0x112(ParserState* parser)
{
    // Save current token to backup
    parser->tokenBackup = parser->unknown4;

    // Check if we already have a lookahead token
    if (parser->lookaheadTokenType == TOKEN_EOF) {
        // No lookahead: read the next token directly into current
        int32_t token = Parser::readNextToken(&parser->nextTokenBuffer);
        parser->currentToken = token;
    } else {
        // Use the lookahead token as current, and shift the further lookahead
        parser->currentToken = parser->lookaheadTokenType;
        parser->nextTokenBuffer = parser->furtherLookaheadToken;
        parser->lookaheadTokenType = TOKEN_EOF;
    }

    // Consume the token (advance the parser)
    int32_t consumeResult = Parser::consumeToken(parser);
    if (consumeResult == 1) {
        // Set global flag something to 3 (e.g., error recovery)
        // Note: Ghidra decompiled *in_EAX; we assume it's modifying the return value's address, but likely it's a global.
        // We'll replicate as a write to a specific address; for now use a placeholder.
        int32_t* globalFlag = (int32_t*)0x00e2a904; // from error string; not correct, but just placeholder
        *globalFlag = 3;
    }

    // Update parser stack after token consumption
    Parser::updateParseStack();

    // Get the child state pointer
    ParserState* child = parser->childState;

    // Copy some field from child
    child->unknown4 = child->nextTokenBuffer;   // +0x1c = +0x18 (assuming +0x18 is nextTokenBuffer)
    Parser::resetSubparser(child);

    // Check if the current token is the expected one
    if (parser->currentToken == EXPECTED_TOKEN) {
        // Save current token to backup again (redundant)
        parser->tokenBackup = parser->unknown4;

        // Read next token similarly (as above)
        if (parser->lookaheadTokenType == TOKEN_EOF) {
            int32_t token = Parser::readNextToken(&parser->nextTokenBuffer);
            parser->currentToken = token;
        } else {
            parser->currentToken = parser->lookaheadTokenType;
            parser->nextTokenBuffer = parser->furtherLookaheadToken;
            parser->lookaheadTokenType = TOKEN_EOF;
        }

        // Stack manipulation: push current parse state onto a linked list
        // This uses local variables that might be used to simulate a stack.
        // The original code did:
        // local_18 = -1;
        // local_c = 0;
        // local_14 = child->someField; (child+0x34)
        // local_10 = 0;
        // local_1c = child->someOther; (child+0x14)
        // *(int**)(child+0x14) = &local_1c; // push address of local onto list
        // We'll replicate this as a stack operation.
        struct StackEntry {
            int32_t field0; // -1
            int32_t field1; // 0
            int32_t field2; // child+0x34
            int32_t field3; // 0
            int32_t field4; // child+0x14
        };
        StackEntry entry;
        entry.field0 = -1;
        entry.field1 = 0;
        entry.field2 = child->unknown34; // offset 0x34
        entry.field3 = 0;
        entry.field4 = child->someOtherField; // offset 0x14
        // Link the child's pointer to this stack entry (dangerous, but matches game code)
        *(int32_t**)((uint8_t*)child + 0x14) = &entry.field4;

        // Execute the final action and finalize
        Parser::executeFinalAction(parser);
        Parser::finalizeParse();
        return;
    }

    // Token mismatch: report error and trigger breakpoint
    errorPrintf("`%s' expected", (void*)0x00e2a904);  // string pointer from data
    errorAbort();
    __asm { int 3 } // software breakpoint
    // Unreachable
}