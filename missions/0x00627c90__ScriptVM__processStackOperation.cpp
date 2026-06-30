// FUNC_NAME: ScriptVM::processStackOperation
// Address: 0x00627c90
// This function appears to implement a stack operation (likely "dup" or "normalize and duplicate")
// for a script virtual machine. It handles type normalization (types 3 and 4) and a special
// case when the element below the top has a zero type tag (triggers a more complex sequence).

struct ScriptVMContext {
    // +0x00: unknown
    // +0x04: unknown
    int* stackPointer; // +0x08
    // +0x0C: unknown
    struct StackInfo {
        int unknown1; // +0x10+0x00
        int unknown2; // +0x10+0x04
        int unknown3; // +0x10+0x08
        int unknown4; // +0x10+0x0C
        int stackSize; // +0x10+0x20
        int stackCapacity; // +0x10+0x24
        int unknown5; // +0x10+0x28
        int unknown6; // +0x10+0x2C
        int elementSize; // +0x10+0x30
    }* stackInfo; // +0x10
};

// Forward declarations of helper functions (renamed for clarity)
void pushValue(ScriptVMContext* ctx, int arg); // FUN_00625ca0
int* getTypeDescriptorForIntFloat(); // FUN_00637f10
int* getTypeDescriptorForFloat(); // FUN_00637f90
int* getTypeDescriptorForOther(); // FUN_00637ea0
void growStack(); // FUN_00627360
int allocateValue(int a, int b); // FUN_00637c50
int* allocateStackSpace(ScriptVMContext* ctx, int size); // FUN_00638020

int ScriptVM::processStackOperation(ScriptVMContext* ctx, int arg) {
    pushValue(ctx, arg);
    int* stackPtr = ctx->stackPointer;
    int typeTag = *(stackPtr - 2); // offset -8 from stack pointer
    int value = *(stackPtr - 1);   // offset -4

    if (typeTag == 3) {
        // Type 3: float that might be integer
        if ((float)(int)value == *(float*)&value) {
            int* typeDesc = getTypeDescriptorForIntFloat();
            // Overwrite type and value with canonical representation
            *(stackPtr - 2) = *typeDesc;
            *(stackPtr - 1) = typeDesc[1];
        }
    } else if (typeTag == 4) {
        int* typeDesc = getTypeDescriptorForFloat();
        *(stackPtr - 2) = *typeDesc;
        *(stackPtr - 1) = typeDesc[1];
    } else {
        int* typeDesc = getTypeDescriptorForOther();
        *(stackPtr - 2) = *typeDesc;
        *(stackPtr - 1) = typeDesc[1];
    }

    int* prevStackPtr = ctx->stackPointer - 2; // points to element below top
    if (prevStackPtr != nullptr && *prevStackPtr == 0) {
        // Special case: element below top has zero type tag
        ctx->stackPointer = prevStackPtr; // pop top element
        if (ctx->stackInfo->stackSize <= ctx->stackInfo->stackCapacity) {
            growStack();
        }
        int* newTop = ctx->stackPointer;
        *newTop = 5; // type 5
        newTop[1] = allocateValue(0, 0);
        ctx->stackPointer += 2; // push new value

        pushValue(ctx, arg);

        // Duplicate the previous top (which is now at stackPointer[-4] and stackPointer[-3])
        int* dupTarget = ctx->stackPointer;
        *dupTarget = dupTarget[-4];
        dupTarget[1] = dupTarget[-3];
        ctx->stackPointer += 2;

        // Allocate space and store the two values from the stack (the original top and the new value?)
        int* allocPtr = allocateStackSpace(ctx, ctx->stackInfo->elementSize);
        *allocPtr = *(ctx->stackPointer - 2);
        allocPtr[1] = *(ctx->stackPointer - 1);
        ctx->stackPointer -= 4; // pop two items

        // Duplicate the new top (which is now at stackPointer[-2] and stackPointer[-1])
        int* dupTarget2 = ctx->stackPointer;
        *dupTarget2 = dupTarget2[-2];
        dupTarget2[1] = dupTarget2[-1];
        ctx->stackPointer += 2;

        pushValue(ctx, arg);

        // Again allocate space and store
        int* allocPtr2 = allocateStackSpace(ctx, ctx->stackInfo->elementSize);
        *allocPtr2 = *(ctx->stackPointer - 2);
        allocPtr2[1] = *(ctx->stackPointer - 1);
        ctx->stackPointer -= 4;

        return 1;
    }
    return 0;
}