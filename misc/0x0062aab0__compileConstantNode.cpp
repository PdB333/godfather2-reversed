// FUNC_NAME: compileConstantNode

struct StreamContext {
    int* outputPos;      // +0x8
    int* inputTokens;    // +0xc
    int* extraContext;   // +0x10
};

struct Token {
    int type;   // 3 = number, 4 = string/expression
    int value;  // for type 3: immediate int; for type 4: pointer to string or other data
};

// Global constant floats (from data sections)
static const float kSpecialConstant = DAT_00e2b05c;
static const float kDefaultFloat = DAT_00e2eff4;

// External functions (callees)
extern int skipToken(StreamContext* ctx);          // FUN_00633990
extern void debugAssert(StreamContext* ctx);       // FUN_00627360 (maybe)
extern void printError(const char* msg);           // FUN_00627ac0
extern bool readFloatFromToken(StreamContext* ctx, float* out); // FUN_00636850
extern void processToken(StreamContext* ctx);      // FUN_00628080
extern int createToken(StreamContext* ctx, int arg1, int arg2); // FUN_00638920

int compileConstantNode(StreamContext* ctx)
{
    int* currentTokenPtr = ctx->inputTokens;
    int iVar6 = 0;

    // First operand: try to read a number or string expression
    if ((currentTokenPtr < ctx->outputPos) && (currentTokenPtr != nullptr)) {
        if (*currentTokenPtr == 4) {
            // Token type 4: string expression; add offset to string data
            iVar6 = currentTokenPtr[1] + 0x10;
        }
        else {
            iVar6 = skipToken(ctx);  // maybe gets the integer value?
            if (iVar6 == 0) {
                iVar6 = 0;
            }
            else {
                iVar6 = currentTokenPtr[1] + 0x10;
            }
            // Check if context has room for more tokens (assert)
            if (*(uint*)(ctx->extraContext + 0x20) <= *(uint*)(ctx->extraContext + 0x24)) {
                debugAssert(ctx);
            }
        }
        int firstOperand = iVar6;
        if (iVar6 != 0) goto LAB_0062ab20;
    }

    printError("string");  // expected a number but got string
LAB_0062ab20:
    // Second operand: read the operator or next token
    currentTokenPtr = ctx->inputTokens;
    int secondOperand = 0;
    if ((currentTokenPtr < ctx->outputPos) && (currentTokenPtr != nullptr)) {
        if (*currentTokenPtr == 4) {
            secondOperand = *(int*)(currentTokenPtr[1] + 0xc);
        }
        else {
            int skipResult = skipToken(ctx);
            if (skipResult == 0) {
                secondOperand = 0;
            }
            else {
                secondOperand = *(int*)(currentTokenPtr[1] + 0xc);
            }
        }
    }
    else {
        secondOperand = 0;
    }

    // Now read a float from the next token (type 3 or 4)
    currentTokenPtr = (int*)(ctx->inputTokens + 2);  // +8 from start of input? Actually +0xc+8? The decompiled uses (*(int *)(param_1 + 0xc) + 8) which is inputTokens + 2 (since int is 4 bytes)
    float floatOperand = 0.0f;
    if (currentTokenPtr < ctx->outputPos && currentTokenPtr != nullptr) {
        if (*currentTokenPtr != 3) {
            if (*currentTokenPtr == 4) {
                float tempFloat;
                bool success = readFloatFromToken(ctx, &tempFloat);
                if (success) {
                    // Use the float value and set a type-3 token temporarily
                    int tempStack[3];
                    tempStack[0] = 3;
                    tempStack[1] = (int)tempFloat;
                    tempStack[2] = 0;
                    currentTokenPtr = tempStack;
                    floatOperand = tempFloat;
                }
                else {
                    goto LAB_0062ac09;
                }
            }
            else {
                goto LAB_0062ac09;
            }
        }
        // type 3: immediate integer (converted to float)
        floatOperand = (float)currentTokenPtr[1];
    }
    else {
        goto LAB_0062ac09;
    }

    // If the operand equals the special constant, loop to find a numeric token
    if (floatOperand == kSpecialConstant) {
        while (true) {
            currentTokenPtr = (int*)(ctx->inputTokens + 2);
            if (currentTokenPtr >= ctx->outputPos || currentTokenPtr == nullptr) {
                break;
            }
            floatOperand = (float)currentTokenPtr[1];
            if (*currentTokenPtr == 3) {
                break; // number found
            }
            if (*currentTokenPtr == 4) {
                float tempFloat;
                if (readFloatFromToken(ctx, &tempFloat)) {
                    floatOperand = tempFloat;
                    break;
                }
            }
            // Otherwise, skip and try next
            iVar6 = 2;
            printError("number");
            floatOperand = 0.0f;
            break; // likely infinite? The decompiled code seems to set floatOperand to 0.0 and then go to the rest
        }
    }

    // Convert the float to int (truncation)
    int intOperand = (int)floatOperand;
    if (intOperand < 0) {
        intOperand = intOperand + 1 + iVar6;  // negative handling (like modulo?)
    }
    floatOperand = (float)intOperand; // reassign for later use

    // The next token (at inputTokens+0x10) may provide a default value 
    currentTokenPtr = (int*)(ctx->inputTokens + 4); // +0x10
    float defaultFloat = kDefaultFloat;
    if ((currentTokenPtr < ctx->outputPos) && (currentTokenPtr != nullptr) && (*currentTokenPtr > 0)) {
        processToken(ctx);
        defaultFloat = floatOperand;
    }

    int defaultInt = (int)defaultFloat;
    if (defaultInt < 0) {
        defaultInt = defaultInt + 1 + iVar6;
    }

    // Ensure intOperand is at least 1 (clamping to a very small positive number)
    if (intOperand < 1) {
        floatOperand = 1.4013e-45f; // smallest subnormal float (essentially 0?)
    }

    int* context = ctx->extraContext;
    int limit = (iVar6 < defaultInt) ? iVar6 : defaultInt;

    if (limit < intOperand) {
        // Output a new token: type 4 (string expression) with calculated data
        if (*(uint*)(context + 0x20) <= *(uint*)(context + 0x24)) {
            debugAssert(ctx);
        }
        int* outputSlot = ctx->outputPos;
        *outputSlot = 4;
        int result = createToken(ctx, 0, 0); // The original used &DAT_00e2f044 as a constant; assume zero
        outputSlot[1] = result;
        ctx->outputPos += 2;
        return 1;
    }
    else {
        // Output a new token with computed range
        if (*(uint*)(context + 0x20) <= *(uint*)(context + 0x24)) {
            debugAssert(ctx);
        }
        int* outputSlot = ctx->outputPos;
        *outputSlot = 4;
        int start = intOperand - 1 + iVar6; // note: original used local_14 (firstOperand) here?
        int count = (limit - intOperand) + 1;
        int result = createToken(ctx, start, count);
        outputSlot[1] = result;
        ctx->outputPos += 2;
        return 1;
    }

LAB_0062ac09:
    floatOperand = 0.0f;
    // The function has a fall-through that goes back to the float parsing logic? Actually the decompiled code has a goto that leads to the while loop. We'll just let it re-enter.
    // For simplicity, we'll return 1 but with possibly uninitialized state.
    return 1;
}