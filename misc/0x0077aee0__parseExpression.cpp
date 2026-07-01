// FUNC_NAME: parseExpression
// Reconstructed C++ code for expression parser (The Godfather 2 script/condition evaluator)

struct ParseContext {
    const char* input;    // +0x00
    int position;         // +0x04
};

enum NodeType : int {
    NT_None = 0,
    NT_BooleanLiteral  = 1, // 0xb? Actually stored in field
    NT_Variable        = 2,
    NT_Number          = 3,
    NT_Not             = 0xb, // opcode for unary NOT
    // ... others
};

struct ASTNode {
    void** vtable;        // +0x00
};

struct BooleanLiteralNode : ASTNode {
    // size 0x8
    // +0x00: vtable (PTR_LAB_00d684bc)
    char value;           // +0x04
};

struct VariableNode : ASTNode {
    // size 0x8
    // +0x00: vtable (PTR_LAB_00d684a8)
    int variableId;       // +0x04
};

struct UnaryOpNode : ASTNode {
    // size 0x14
    // +0x00: vtable (PTR_FUN_00d68494)
    int opcode;           // +0x04
    ASTNode* child;       // +0x08
    int unused1;          // +0x0C
    int unused2;          // +0x10
};

struct BinaryOpNode : ASTNode {
    // size 0x14
    // vtable same as UnaryOpNode? Possibly different.
    int opcode;           // +0x04
    ASTNode* left;        // +0x08? (layout may vary)
    ASTNode* right;       // +0x0C
    int something;        // +0x10
};

// Forward declarations for helper functions (stubs)
int parseParenthesisLength(ParseContext* ctx);
ASTNode* parsePrimitive(ParseContext* ctx);
ASTNode* parseVariableOrNumber(ParseContext* ctx);
ASTNode* createBinaryOp(int opcode, ASTNode* left, ASTNode* right);
int parseOperator(ParseContext* ctx);
ASTNode* parseExpression(ParseContext* ctx);

// Memory allocation (FUN_009c8e50)
void* operator new(size_t size);

// Debug/log functions (stubs)
void pushLogStack(int level);      // FUN_004d53a0
void advancePosition(int delta1, int delta2); // FUN_004d45e0
void skipWhitespace(ParseContext* ctx); // FUN_004d3b50
bool tryParseSymbol(ParseContext* ctx, char* outChar); // FUN_0077ab80
bool tryParseVariable(ParseContext* ctx, int* outId); // FUN_0077abd0
int parseNumber(ParseContext* ctx); // FUN_0077ac20
ASTNode* createNumberLiteral(int value); // FUN_0077a910

// Global vtable pointers (from data section)
extern void* PTR_LAB_00d684bc; // vtable for BooleanLiteralNode
extern void* PTR_LAB_00d684a8; // vtable for VariableNode
extern void* PTR_FUN_00d68494; // vtable for UnaryOpNode/BinaryOpNode

ASTNode* parseExpression(ParseContext* ctx) {
    ASTNode* result = nullptr;
    
    if (ctx->position == 0) {
        // Base case: empty input -> allocate a placeholder? (Not clear)
        // Actually the original checks param_1[1] == 0, meaning position==0.
        // That likely means we are at the start of a new subexpression.
        // In such case, allocate a dummy node? It creates a BooleanLiteralNode with value 1.
        BooleanLiteralNode* node = (BooleanLiteralNode*)operator new(8);
        if (node) {
            node->vtable = &PTR_LAB_00d684bc;
            node->value = 1; // true
            return node;
        }
        return nullptr;
    }
    
    // Logging (maybe debug)
    pushLogStack(0x20);
    
    bool isNegated = false;
    if (ctx->input[ctx->position] == '!') {
        isNegated = true;
        advancePosition(0, 1);  // skip '!'
        pushLogStack(0x20);
    }
    
    if (ctx->input[ctx->position] == '(') {
        int parenLength = parseParenthesisLength(ctx);
        if ((unsigned int)ctx->position >= parenLength) {
            // Error: malformed parenthesis? In original code, if position >= parenLength, it calls error and recurses.
            advancePosition(0, 1); // skip '('?
            result = parseExpression(ctx);
            // then create a negation node if needed (handled later)
        } else {
            // skip '(' and '(' again? Actually original code does:
            // FUN_004d3b50(param_1); // skip '('
            // FUN_004d3b50(param_1); // skip the next char? Or skip whitespace?
            // FUN_004d45e0(uVar3, param_1[1] - uVar3); // skip everything inside the parentheses?
            // Then parse the interior.
            skipWhitespace(ctx);
            skipWhitespace(ctx);
            advancePosition(parenLength, ctx->position - parenLength);
            advancePosition(0, 1);
            
            // Now parse the interior expression
            ParseContext subCtx; // local_20 etc.
            memset(&subCtx, 0, sizeof(subCtx));
            ASTNode* child = parseExpression(&subCtx);
            
            if (isNegated) {
                // Create a unary NOT node wrapping child
                UnaryOpNode* node = (UnaryOpNode*)operator new(0x14);
                if (node) {
                    node->vtable = &PTR_FUN_00d68494;
                    node->opcode = 0xb; // NOT
                    node->child = child;
                    node->unused1 = 0;
                    node->unused2 = 2;
                }
                result = node;
                isNegated = false; // already handled
            } else {
                result = child;
            }
            
            // Skip over the matched parentheses and interior? Advance position.
            advancePosition(0, parenLength + 1);
            
            // Now parse an operator and right side if present
            int opcode = parseOperator(ctx); // via FUN_004d46f0 etc.
            if (opcode != 0) {
                // There is a following operator and another expression
                ParseContext rhsCtx; // local_30 etc.
                ASTNode* right = parseExpression(&rhsCtx);
                result = createBinaryOp(opcode, result, right);
            }
        }
    } else {
        // Parse a token (literal, variable, etc.)
        ParseContext subCtx; // local_20
        ParseContext opsCtx; // local_30
        memset(&subCtx, 0, sizeof(subCtx));
        memset(&opsCtx, 0, sizeof(opsCtx));
        
        // Try to parse a symbol (char) or variable or number
        char singleChar = 0;
        int variableId = 0;
        if (tryParseSymbol(ctx, &singleChar)) {
            // Boolean literal? Actually symbol parsing gives a char.
            BooleanLiteralNode* node = (BooleanLiteralNode*)operator new(8);
            if (node) {
                node->vtable = &PTR_LAB_00d684bc;
                node->value = singleChar; // e.g., 'T' or 'F'
            }
            result = node;
        } else if (tryParseVariable(ctx, &variableId)) {
            VariableNode* node = (VariableNode*)operator new(8);
            if (node) {
                node->vtable = &PTR_LAB_00d684a8;
                node->variableId = variableId;
            }
            result = node;
        } else {
            // Must be a number
            int value = parseNumber(ctx);
            result = createNumberLiteral(value);
        }
        
        // Apply negation if needed (wrapping)
        if (isNegated) {
            UnaryOpNode* node = (UnaryOpNode*)operator new(0x14);
            if (node) {
                node->vtable = &PTR_FUN_00d68494;
                node->opcode = 0xb; // NOT
                node->child = result;
                node->unused1 = 0;
                node->unused2 = 2;
            }
            result = node;
            isNegated = false;
        }
        
        // Now parse operator and rhs (if present)
        int opcode = parseOperator(ctx);
        if (opcode != 0) {
            // Must parse another expression
            // ORIGINAL: It checks something about opsCtx.local_30 etc.
            // We'll assume operator parsing sets up a context.
            ParseContext rhsCtx;
            ASTNode* right = parseExpression(&rhsCtx);
            result = createBinaryOp(opcode, result, right);
        }
    }
    
    // Clean up any sub-context buffers (destructors, etc.) - omitted for clarity
    return result;
}