// FUNC_NAME: Parser::parseExpressionWithStack

struct ParserContext {
    int reserved;          // +0x00
    int prevTokenValue;    // +0x04
    int currTokenValue;    // +0x08
    int tokenType;         // +0x0c
    int subExpression;     // +0x10
    int opToken;           // +0x14
    int nextToken;         // +0x18
    int* stack;            // +0x1c
};

struct TokenInfo {
    int type;   // 0
    int value;  // 4
};

// Forward declarations (assumed from callees)
void advanceToken(ParserContext* ctx);
int parsePrimaryExpression(int* exprOut);
TokenInfo* getCurrentTokenInfo();
void pushOperand(int index);
void errorReport(const char* msg);

int Parser::parseExpressionWithStack(ParserContext* ctx)
{
    int counter = 1;

    advanceToken(ctx);

    do {
        // If the current token is not the expected operator (0x2c), return count
        if (ctx->tokenType != 0x2c) {
            return counter;
        }

        // Save previous token value
        ctx->currTokenValue = ctx->prevTokenValue;

        if (ctx->opToken == 0x11f) { // token for primary expression?
            // Parse a primary expression and store its type
            ctx->tokenType = parsePrimaryExpression(&ctx->subExpression);
        }
        else {
            // Shift tokens: current becomes the operator, next becomes sub-expression
            ctx->tokenType = ctx->opToken;
            ctx->subExpression = ctx->nextToken;
            ctx->opToken = 0x11f; // reset to primary marker
        }

        int* localStack = ctx->stack;
        TokenInfo* currToken = getCurrentTokenInfo();

        // If current token is identifier (0xb) and its value is within a valid range,
        // decrease the complexity counter (operator precedence?)
        if ((currToken->type == 0xb) &&
            (currToken->value >= localStack[13]) &&
            (currToken->value < 0xfa)) {
            localStack[9]--;
        }

        int complexity = localStack[9] + 1;
        unsigned char* maxComplexity = (unsigned char*)(localStack[0] + 0x47);

        if (complexity > *maxComplexity) {
            if (complexity > 0xf9) {
                errorReport("function or expression too complex");
                return counter;
            }
            *maxComplexity = (char)complexity;
        }

        localStack[9] = complexity;
        pushOperand(complexity - 1);

        advanceToken(ctx);
        counter++;
    } while (true);
}