// FUNC_NAME: ScriptVM::printArguments
// Function address: 0x0046bce0
// Decompiled reconstruction of the EARS scripting VM print function.
// Prints a variable number of arguments, converting each to string via tostring method.

#define STACK_ENTRY_SIZE 8

// Error message when tostring doesn't return a string
static const char* kErrTostringMustReturnString = "`tostring' must return a string to `print'";

// Global function pointers for output
extern void (*gPrintFunc)(const char*, int, const char*, const char*);
extern void gPrintFallback(const char*, int, const char*, const char*); // if gPrintFunc is null

// Forward declarations of VM helper functions
int ScriptVM_getMethodByName(int context, const char* methodName);
char* ScriptVM_convertToString(int context, int buffer, int stackEntry, int flags);
void ScriptVM_pushStringToStack(int context, int stackEntry, int isString);
int ScriptVM_isStringType(int context);
void ScriptVM_clearStack(int context);
void ScriptVM_releaseString(int context);
void ScriptVM_acquireString(int context);
void ScriptVM_freeTemporaryString(int context);
void ScriptVM_incrementRefCount(int context);
void ScriptVM_decrementRefCount(int context);

// Structure representing a stack node (type + value)
// Each entry is 8 bytes: 4 bytes type, 4 bytes value.
#pragma pack(push, 1)
struct StackNode {
    uint32_t type;   // +0x00: type tag (e.g., 4 = string)
    uint32_t value;  // +0x04: value (pointer or integer)
};
#pragma pack(pop)

// VM context structure (partial)
struct ScriptContext {
    // +0x00: unknown (maybe vtable?)
    // +0x04: unknown
    StackNode* stackTop;      // +0x08: pointer to current top of stack
    StackNode* stackBase;     // +0x0C: pointer to stack base (end of allocated area?)
    uint32_t stringTop;       // +0x10: pointer to some string reference list
    uint32_t stringFreeCount; // +0x14: count of free string slots? (used in loop)
    // ... more fields
    char* stringBuffer;       // +0x40: temporary string buffer for conversion
    uint32_t maxStringCount;  // +0x28: max allowed strings? (used in loop)
    // other fields...
};

int ScriptVM::print(void* context) {
    ScriptContext* ctx = (ScriptContext*)context;
    uint32_t numArgs = (ctx->stackTop - ctx->stackBase) / STACK_ENTRY_SIZE; // number of arguments on stack

    // Get the "tostring" method
    ScriptVM_getMethodByName(ctx, "tostring");
    // Convert the topmost argument to string (requires a buffer)
    char* str = ScriptVM_convertToString(ctx, (int)&ctx->stringBuffer, (int)(ctx->stackTop - 1), 0);
    // Push the converted string onto stack (it replaces the original argument with the string)
    ctx->stackTop->type = str[0];
    ctx->stackTop->type = str[0]; // questionable, but per decomp: *(int*)(top-8) = *puVar1; *(int*)(top-4)=puVar1[1]; then top = top+8.
    ctx->stackTop->value = *((uint32_t*)(str+4));
    ctx->stackTop += 1; // actually it's moved by 8 bytes, but we treat as node increment

    // Now process each argument: for each, pop, convert to string, and print
    int argIndex = 0; // local variable piVar8, starts at 1? Actually it's a loop counter starting from 1.
    // The decompiled loop uses piVar8 as index, but it starts at 1 and goes to numArgs.
    // We'll refactor for clarity.
    for (argIndex = 1; argIndex <= numArgs; argIndex++) {
        StackNode* currentEntry = ctx->stackTop; // actually currentEntry == ctx->stackTop (after previous push)
        // Copy the previous entry (which is a string) to the current position? This is confusing.
        // The decompile does: *puVar1 = puVar1[-2]; puVar1[1] = puVar1[-1]; then top += 8.
        // This seems to be duplicating the string? Or moving stack pointers? Might be a stack rotation.
        *currentEntry = *(currentEntry - 2); // copy value from two positions back
        ctx->stackTop += 1;

        // Now fetch the argument at position determined by piVar8 relative to stack base
        StackNode* argNode;
        if (argIndex < 0) {
            // Negative indices? (unlikely for positive loop, but code has branches)
            // The decompiled code had a complicated condition for negative piVar8.
            // We'll simplify: assume piVar8 is always positive here.
            argNode = ctx->stackBase - 1 + (argIndex * 2); // +2? Actually piVar8 is used as index directly
            // The original code had: puVar2 = (uint*)(ctx->stackBase - 8 + piVar8 * 8);
        } else {
            argNode = ctx->stackBase - 1 + (argIndex * 2);
        }

        // Copy the argument data to the current stack position
        *currentEntry = *argNode;
        ctx->stackTop += 1; // advance top again

        // Now process this entry: convert to string if needed
        ScriptVM_pushStringToStack(ctx, (int)(ctx->stackTop - 2), 1); // mark as string? or convert
        StackNode* entry = (StackNode*)(ctx->stackTop - 1); // actually - (int)ctx->stackTop + 8? Original: local_84 = iVar7 + -8

        if (entry->type == 4) { // Type 4 = string pointer
            entry = (StackNode*)(entry->value + 0x10); // dereference string object
        } else {
            int isString = ScriptVM_isStringType(ctx);
            if (!isString) {
                entry = nullptr;
            } else {
                entry = (StackNode*)(entry->value + 0x10);
            }
            // Check for overflow in string reference list
            uint32_t usedStrings = *(uint32_t*)(ctx->stringTop + 0x20);
            uint32_t maxStrings = *(uint32_t*)(ctx->stringTop + 0x24);
            if (usedStrings <= maxStrings) {
                // Acquire and release string (reference counting)
                ScriptVM_acquireString(ctx); // indirect calls
                ScriptVM_clearStack(ctx, 0);
                ScriptVM_releaseString(ctx);
                ScriptVM_clearStack(ctx, 0);
                ScriptVM_freeTemporaryString(ctx);
                ScriptVM_decrementRefCount(ctx);
            }
        }

        if (entry == nullptr) {
            // Error: tostring did not return a string
            ScriptVM_printError(ctx, kErrTostringMustReturnString);
            // The function jumps to label LAB_0046bee9 which prints error and then to cleanup
            goto errorCleanup;
        }

        // If argIndex > 1, print a space separator
        // The original code calls FUN_004d4300(&DAT_00e327b4) for each argument beyond first
        // DAT_00e327b4 is likely a global string constant " " (space)
        if (argIndex > 1) {
            ScriptVM_appendString(ctx, &gSpaceString);
        }

        // Append the argument string
        ScriptVM_appendString(ctx, entry);

        // Pop the temporary entry (just processed) from stack
        ctx->stackTop -= 1;
    }

    // After processing all arguments, append newline or final terminator
    ScriptVM_appendString(ctx, &gNewlineString);

    // The following loop at the end (from decompiled after label LAB_0046bf26) seems to be error handling
    // It cleans up pending string references.
    // We'll replicate the logic for safety.

    // Cleanup: iterate backwards through string reference list to free any remaining strings
    uint32_t strRef = ctx->stringTop; // starting from current
    uint32_t strRefMax = ctx->maxStringCount;
    int count = 1;
    // The loop decreases a counter while checking a byte flag and a -field
    do {
        if (strRef > strRefMax) break;
        count--;
        if ((*(uint8_t*)(strRef + 8) & 1) == 0) {
            count -= *(int*)(strRef + 0x14);
        }
        strRef -= 0x18; // move to previous string record (each record is 0x18 bytes)
    } while (count > 0);

    // More error message building (the code uses local_84, local_64, etc.)
    // This part is unclear but appears to handle global error formatting.
    // We'll compress it to: if error condition, print error string.
    if (gErrorCondition) {
        ScriptVM_outputError(ctx, gErrorFormat, gErrorArgs...);
    }

    return 0;

errorCleanup:
    // Label LAB_0046bf26
    ScriptVM_clearStack(ctx, &gEmptyString); // some string constant
    // Additional cleanup for error state
    // The code sets local_84, local_64, local_5c, local_58, local_54 and then calls gPrintFunc
    // We'll abstract as:
    if (gPrintFunc) {
        gPrintFunc(gErrorStr1, 0, gErrorStr2, nullptr);
    }
    return 0;
}

// Helper functions (stubs for the actual VM functions called)
void ScriptVM_printError(void* ctx, const char* msg) {
    // Outputs error message to console
    ScriptVM_appendString(ctx, msg);
}

void ScriptVM_appendString(void* ctx, const void* str) {
    // Appends string to the print buffer
    // Calls FUN_004d4300 which likely concatenates to a global string
}

// Global constants
char gSpaceString[] = " ";
char gNewlineString[] = "\n";
int gErrorCondition = 0; // placeholder

// Note: The decompiled code also references FUN_004d4300 with global addresses like DAT_00e327b4 (space) and DAT_00e327b8 (newline).
// We have replaced those with symbolic constants.// FUNC_NAME: ScriptVM::printArguments
// Function address: 0x0046bce0
// Decompiled reconstruction of the EARS scripting VM print function.
// Prints a variable number of arguments, converting each to string via tostring method.

#define STACK_ENTRY_SIZE 8

// Error message when tostring doesn't return a string
static const char* kErrTostringMustReturnString = "`tostring' must return a string to `print'";

// Global function pointers for output
extern void (*gPrintFunc)(const char*, int, const char*, const char*);
extern void gPrintFallback(const char*, int, const char*, const char*); // if gPrintFunc is null

// Forward declarations of VM helper functions
int ScriptVM_getMethodByName(int context, const char* methodName);
char* ScriptVM_convertToString(int context, int buffer, int stackEntry, int flags);
void ScriptVM_pushStringToStack(int context, int stackEntry, int isString);
int ScriptVM_isStringType(int context);
void ScriptVM_clearStack(int context);
void ScriptVM_releaseString(int context);
void ScriptVM_acquireString(int context);
void ScriptVM_freeTemporaryString(int context);
void ScriptVM_incrementRefCount(int context);
void ScriptVM_decrementRefCount(int context);

// Structure representing a stack node (type + value)
// Each entry is 8 bytes: 4 bytes type, 4 bytes value.
#pragma pack(push, 1)
struct StackNode {
    uint32_t type;   // +0x00: type tag (e.g., 4 = string)
    uint32_t value;  // +0x04: value (pointer or integer)
};
#pragma pack(pop)

// VM context structure (partial)
struct ScriptContext {
    // +0x00: unknown (maybe vtable?)
    // +0x04: unknown
    StackNode* stackTop;      // +0x08: pointer to current top of stack
    StackNode* stackBase;     // +0x0C: pointer to stack base (end of allocated area?)
    uint32_t stringTop;       // +0x10: pointer to some string reference list
    uint32_t stringFreeCount; // +0x14: count of free string slots? (used in loop)
    // ... more fields
    char* stringBuffer;       // +0x40: temporary string buffer for conversion
    uint32_t maxStringCount;  // +0x28: max allowed strings? (used in loop)
    // other fields...
};

int ScriptVM::print(void* context) {
    ScriptContext* ctx = (ScriptContext*)context;
    uint32_t numArgs = (ctx->stackTop - ctx->stackBase) / STACK_ENTRY_SIZE; // number of arguments on stack

    // Get the "tostring" method
    ScriptVM_getMethodByName(ctx, "tostring");
    // Convert the topmost argument to string (requires a buffer)
    char* str = ScriptVM_convertToString(ctx, (int)&ctx->stringBuffer, (int)(ctx->stackTop - 1), 0);
    // Push the converted string onto stack (it replaces the original argument with the string)
    ctx->stackTop->type = str[0];
    ctx->stackTop->type = str[0]; // questionable, but per decomp: *(int*)(top-8) = *puVar1; *(int*)(top-4)=puVar1[1]; then top = top+8.
    ctx->stackTop->value = *((uint32_t*)(str+4));
    ctx->stackTop += 1; // actually it's moved by 8 bytes, but we treat as node increment

    // Now process each argument: for each, pop, convert to string, and print
    int argIndex = 0; // local variable piVar8, starts at 1? Actually it's a loop counter starting from 1.
    // The decompiled loop uses piVar8 as index, but it starts at 1 and goes to numArgs.
    // We'll refactor for clarity.
    for (argIndex = 1; argIndex <= numArgs; argIndex++) {
        StackNode* currentEntry = ctx->stackTop; // actually currentEntry == ctx->stackTop (after previous push)
        // Copy the previous entry (which is a string) to the current position? This is confusing.
        // The decompile does: *puVar1 = puVar1[-2]; puVar1[1] = puVar1[-1]; then top += 8.
        // This seems to be duplicating the string? Or moving stack pointers? Might be a stack rotation.
        *currentEntry = *(currentEntry - 2); // copy value from two positions back
        ctx->stackTop += 1;

        // Now fetch the argument at position determined by piVar8 relative to stack base
        StackNode* argNode;
        if (argIndex < 0) {
            // Negative indices? (unlikely for positive loop, but code has branches)
            // The decompiled code had a complicated condition for negative piVar8.
            // We'll simplify: assume piVar8 is always positive here.
            argNode = ctx->stackBase - 1 + (argIndex * 2); // +2? Actually piVar8 is used as index directly
            // The original code had: puVar2 = (uint*)(ctx->stackBase - 8 + piVar8 * 8);
        } else {
            argNode = ctx->stackBase - 1 + (argIndex * 2);
        }

        // Copy the argument data to the current stack position
        *currentEntry = *argNode;
        ctx->stackTop += 1; // advance top again

        // Now process this entry: convert to string if needed
        ScriptVM_pushStringToStack(ctx, (int)(ctx->stackTop - 2), 1); // mark as string? or convert
        StackNode* entry = (StackNode*)(ctx->stackTop - 1); // actually - (int)ctx->stackTop + 8? Original: local_84 = iVar7 + -8

        if (entry->type == 4) { // Type 4 = string pointer
            entry = (StackNode*)(entry->value + 0x10); // dereference string object
        } else {
            int isString = ScriptVM_isStringType(ctx);
            if (!isString) {
                entry = nullptr;
            } else {
                entry = (StackNode*)(entry->value + 0x10);
            }
            // Check for overflow in string reference list
            uint32_t usedStrings = *(uint32_t*)(ctx->stringTop + 0x20);
            uint32_t maxStrings = *(uint32_t*)(ctx->stringTop + 0x24);
            if (usedStrings <= maxStrings) {
                // Acquire and release string (reference counting)
                ScriptVM_acquireString(ctx); // indirect calls
                ScriptVM_clearStack(ctx, 0);
                ScriptVM_releaseString(ctx);
                ScriptVM_clearStack(ctx, 0);
                ScriptVM_freeTemporaryString(ctx);
                ScriptVM_decrementRefCount(ctx);
            }
        }

        if (entry == nullptr) {
            // Error: tostring did not return a string
            ScriptVM_printError(ctx, kErrTostringMustReturnString);
            // The function jumps to label LAB_0046bee9 which prints error and then to cleanup
            goto errorCleanup;
        }

        // If argIndex > 1, print a space separator
        // The original code calls FUN_004d4300(&DAT_00e327b4) for each argument beyond first
        // DAT_00e327b4 is likely a global string constant " " (space)
        if (argIndex > 1) {
            ScriptVM_appendString(ctx, &gSpaceString);
        }

        // Append the argument string
        ScriptVM_appendString(ctx, entry);

        // Pop the temporary entry (just processed) from stack
        ctx->stackTop -= 1;
    }

    // After processing all arguments, append newline or final terminator
    ScriptVM_appendString(ctx, &gNewlineString);

    // The following loop at the end (from decompiled after label LAB_0046bf26) seems to be error handling
    // It cleans up pending string references.
    // We'll replicate the logic for safety.

    // Cleanup: iterate backwards through string reference list to free any remaining strings
    uint32_t strRef = ctx->stringTop; // starting from current
    uint32_t strRefMax = ctx->maxStringCount;
    int count = 1;
    // The loop decreases a counter while checking a byte flag and a -field
    do {
        if (strRef > strRefMax) break;
        count--;
        if ((*(uint8_t*)(strRef + 8) & 1) == 0) {
            count -= *(int*)(strRef + 0x14);
        }
        strRef -= 0x18; // move to previous string record (each record is 0x18 bytes)
    } while (count > 0);

    // More error message building (the code uses local_84, local_64, etc.)
    // This part is unclear but appears to handle global error formatting.
    // We'll compress it to: if error condition, print error string.
    if (gErrorCondition) {
        ScriptVM_outputError(ctx, gErrorFormat, gErrorArgs...);
    }

    return 0;

errorCleanup:
    // Label LAB_0046bf26
    ScriptVM_clearStack(ctx, &gEmptyString); // some string constant
    // Additional cleanup for error state
    // The code sets local_84, local_64, local_5c, local_58, local_54 and then calls gPrintFunc
    // We'll abstract as:
    if (gPrintFunc) {
        gPrintFunc(gErrorStr1, 0, gErrorStr2, nullptr);
    }
    return 0;
}

// Helper functions (stubs for the actual VM functions called)
void ScriptVM_printError(void* ctx, const char* msg) {
    // Outputs error message to console
    ScriptVM_appendString(ctx, msg);
}

void ScriptVM_appendString(void* ctx, const void* str) {
    // Appends string to the print buffer
    // Calls FUN_004d4300 which likely concatenates to a global string
}

// Global constants
char gSpaceString[] = " ";
char gNewlineString[] = "\n";
int gErrorCondition = 0; // placeholder

// Note: The decompiled code also references FUN_004d4300 with global addresses like DAT_00e327b4 (space) and DAT_00e327b8 (newline).
// We have replaced those with symbolic constants.