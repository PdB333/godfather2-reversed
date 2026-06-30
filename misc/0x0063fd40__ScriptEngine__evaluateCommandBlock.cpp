// FUNC_NAME: ScriptEngine::evaluateCommandBlock
// Reconstructed from Ghidra decompile of function at 0x0063fd40
// This is a recursive parser/evaluator for a script bytecode format (EARS engine)
// Known classes: ScriptEngine, TokenNode, ScriptState

// Forward declarations of helper functions
void reportError(const char* msg); // FUN_00638b80
bool getNextToken();               // FUN_0063dbf0, returns true if token available
void parseSubExpression(ScriptState* state); // FUN_0063f4f0, modifies local_14, local_18
void evaluateConditional();        // FUN_0063fcb0
void advanceTokenPointer();        // FUN_0063dc30
int evaluateExpression(ScriptState* state); // FUN_0063f220, returns result index
void compareExpressions(int a, int b); // FUN_0063e260
void releaseTokenSlot(void* tokenSlot); // FUN_00643090

// Structure of the interpreter state (param_1)
struct ScriptState {
    /* +0x00 */ uint unknown0;
    /* +0x04 */ uint unknown4;
    /* +0x08 */ uint unknown8;
    /* +0x0C */ int tokenTypeId; // expected value 0x2C (44) for specific construct
    /* +0x10 */ uint unknown10;
    /* +0x14 */ uint unknown14;
    /* +0x18 */ uint unknown18;
    /* +0x1C */ ScriptContext* context; // pointer to execution context
    // ...
};

// Structure of the execution context (pointed by state->context)
struct ScriptContext {
    /* +0x00 */ uint unknown0;
    /* +0x04 */ uint unknown4;
    /* +0x08 */ uint unknown8;
    /* +0x0C */ uint* flagArray; // array of flags (bit manipulations)
    /* ... */
    /* +0x24 */ int offsetAdjustment; // used for offset compensation
};

// Token node structure (param_2)
struct TokenNode {
    /* +0x00 */ uint opcode;  // or token type
    /* +0x04 */ void* nextToken; // pointer to next token (used with advance)
    // ...
};

void ScriptEngine::evaluateCommandBlock(ScriptState* state, TokenNode* tokenNode, int depth) {
    int local_2c;  // set by parseSubExpression
    int local_28;  // set by parseSubExpression
    TokenNode* local_18; // new token node pointer (set by parseSubExpression)
    int local_14;  // token type from subexpression (set by parseSubExpression)

    // Validate token opcode range (expected 5 to 8 for certain constructs)
    if ((*(int*)(tokenNode + 4) < 5) || (8 < *(int*)(tokenNode + 4))) {
        reportError("syntax error");
        // Trap
        __asm__("int3");
        return;
    }

    // Check for a specific token type (0x2C = 44) that indicates a special construct
    if (*(int*)(state + 0xC) == 0x2C) {
        bool hasNext = getNextToken();
        if (hasNext != 0) {
            local_18 = tokenNode; // store current token
            parseSubExpression(state); // may modify local_14, local_18
            if (local_14 == 5) {
                evaluateConditional();
            }
            // Recursively parse the next token
            evaluateCommandBlock(state, &local_18, depth + 1);
            goto LAB_0063fdf0;
        }
    }

    // Advance token pointer (skip current token)
    advanceTokenPointer();

    int resultIndex = evaluateExpression(state);
    if (resultIndex == depth) {
        // If the expression result matches the expected depth, apply flags
        if (local_2c == 0xC) {
            uint* flagPtr = (uint*)(*(int*)(*(int**)(state->context) + 0xC) + local_28 * 4);
            *flagPtr = (*flagPtr & 0xFFFF80BF) | 0x80; // Clear some bits, set bit 7 (0x80)
        }
        releaseTokenSlot(tokenNode + 4);
        return;
    }

    // Otherwise, compare current depth with the result index
    compareExpressions(depth, resultIndex);
    if (depth < resultIndex) {
        // Adjust offset in context if depth is smaller
        int* offsetVar = (int*)(state->context + 0x24);
        *offsetVar = *offsetVar + (depth - resultIndex);
    }

LAB_0063fdf0:
    releaseTokenSlot(tokenNode + 4);
    return;
}