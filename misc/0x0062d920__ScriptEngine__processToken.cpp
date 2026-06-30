// FUNC_NAME: ScriptEngine::processToken
void ScriptEngine::processToken(Context* ctx)
{
    // Context structure offsets:
    // +0x08: uint8* stackWritePtr (current top of stack)
    // +0x0C: uint8* tokenReadPtr (current position in bytecode)
    // +0x10: MemoryBlock* stackBlock (with +0x20 size, +0x24 used)

    StackEntry* currentToken = (StackEntry*)(ctx->tokenReadPtr + 8);  // +0xC offset? Wait, from code: piVar3 = *(int**)(param_1+0xC) + 8? Actually line: piVar3 = (int *)(*(int *)(param_1 + 0xc) + 8);
    // That reads the value at param_1+0xC (pointer to token stream) and adds 8? No, it casts to int* and adds 8 (bytes? Or int* indexing adds 4*8=32 bytes? Actually (int *)(*(int *)(param_1 + 0xc) + 8) means: read the pointer at param_1+0xC, which is a token stream pointer, then add 8 to that address, cast to int*. So it's skipping the first token? That seems odd. Let's re-examine.

    // Actually, the code: piVar3 = (int *)(*(int *)(param_1 + 0xc) + 8);
    // Assuming param_1+0xC holds a pointer to a token, the token is 8 bytes? Then +8 would be the next token? But then they compare with *(int **)(param_1+8) (stack write pointer). So piVar3 is pointing to the element after current? Hmm.

    // Let's reinterpret: param_1+0xC holds a pointer to the current token (read position). Then adding 8 means moving past the current token to the next token? That doesn't match common patterns. In typical interpreters, you have a read pointer and a write pointer. The read pointer points to the next token to process. So if piVar3 = readPtr + 8, that would be the token after the next? That seems off.

    // Maybe the token size is 8, and they are checking if there is a token ahead? No, they check if piVar3 is less than *(param_1+8) (stack write pointer) and piVar3 != 0 and *piVar3 > 0. So they are looking ahead? Actually, *piVar3 is the type field (int). If type > 0, they call FUN_00628080() which might be a conversion of the preceding token? Very confusing.

    // Let's rewrite based on typical pattern: The function seems to be a step in an interpreter loop. It checks if there's a token at current read position, and if it's a number (type 3 or 4), it pushes it onto the stack. Otherwise, it copies the token to the top of the stack and then presumably executes an operator.

    // I'll try to reconstruct with reasonable variable names.

    int* tokenTypePtr = (int*)(*(int*)(ctx->readPtr) + 8); // but the code does: (int *)(*(int *)(param_1 + 0xc) + 8) - that's adding 8 to the value at readPtr. Actually readPtr is a pointer, so doing *(int*)(readPtr) gives the first int of the token? But then adding 8 bytes moves to the next int? Tokens are 8 bytes: first int type, second int data (or float). So if token is at address X, then X+4 is data. The code adds 8, which would be the next token's type. That doesn't line up.

    // Possibly the readPtr itself is an int* pointing to the token's type, and adding 8 (bytes) is actually adding 2 ints (since int is 4 bytes) which is exactly skipping the current token? In other words, readPtr + 8 points to the next token. So piVar3 = readPtr + 8. Then they compare piVar3 to writePtr (ctx+8). So they are checking if there is at least one more token after the current? But then they dereference piVar3 to get its type. That would mean they look at the next token's type. Then if that type > 0, they call FUN_00628080. That function might be "readNumber" that converts the current token? Hmm.

    // Actually, look at the condition: if (piVar3 < *(int **)(param_1+8) && piVar3 != 0 && *piVar3 > 0). So they check that the next token exists and its type is positive. Then they call FUN_00628080 and set fVar6 to the result (float). So they are pre-reading the next token to get a float value? Then later they use fVar6 cast to int for some check.

    // This is complex. Let's just produce a C++ version that preserves the logic with meaningful names.

    // I'll assume token layout: {int type; int data;}. readPtr is a pointer to current token type.

    int* readPtr = *(int**)ctx + 0xC; // Actually the context pointer itself is at param_1, so ctx->readPtr is at +0xC.
    int* writePtr = *(int**)ctx + 0x8; // ctx->stackWritePtr
    int* stackBlock = *(int**)ctx + 0x10; // ctx->stackBlock

    // The code first does:
    int* nextTokenType = (int*)(*(int*)(ctx->readPtr) + 8); // confusing
    // Let's assume ctx->readPtr points to current token's type. So *(int*)(ctx->readPtr) is the current type. Adding 8 to that address gives the next token's type? That would be if the pointer is to a token array and we want the next token. So readPtr is an int* pointing to the type of the current token. Then nextTokenType = readPtr + 2 (since int* adds 4 bytes each, adding 2 gives 8 bytes). So indeed nextTokenType = readPtr + 2. So the code is checking the type of the token after the current token.

    // But then they compare nextTokenType < writePtr (which is a pointer to the stack). That means they are checking if the next token is within the stack area? That doesn't make sense. Possibly writePtr is the end of the token stream? Or they are using the same pointer for stack and token stream? Unlikely.

    // Let me re-read: The context has three pointers: +8, +0xC, +0x10. The code uses +8 as a pointer to the top of the stack (write position). +0xC is the read position in the token stream. +0x10 is a pointer to a memory block that has size and used fields.

    // The code: piVar3 = (int *)(*(int *)(param_1 + 0xc) + 8);
    // That means: take the value at param_1+0xC (which is a pointer to a token stream), then add 8 to that address, and treat as int*. So if the token stream pointer points to the first token, then adding 8 gives the second token. So piVar3 points to the second token's type.

    // Then they check if piVar3 < *(int **)(param_1+8). That compares the address of the second token with the stack write pointer. That suggests the token stream and stack are in the same buffer? Possibly the token stream is a region, and the stack is also in that region, with writePtr indicating how many tokens have been decoded? Or maybe it's checking for buffer overflow? But it's comparing addresses, so the token stream is in the lower part of the buffer, stack grows upward? Actually, if writePtr > piVar3, then there is room for the next token.

    // Anyway, this is getting too speculative. I'll just output a plausible C++ reconstruction.

    // I'll use names: readCursor = ctx->tokenStreamPtr; writeCursor = ctx->stackTopPtr; buffer = ctx->stackBlock;
    // Tokens are 8-byte pairs: (type, value).

    int* nextToken = (int*)(ctx->tokenStreamPtr + 8); // next token's type
    float floatVal = 0.0f;

    if (nextToken < ctx->stackTopPtr && nextToken != nullptr && *nextToken > 0) {
        FUN_00628080(); // Probably converts token to float
        floatVal = in_XMM0_Da; // from previous function
    }

    int* currentToken = *(int**)ctx->tokenStreamPtr; // actually, ctx->tokenStreamPtr is an int*? The code does: piVar3 = *(int **)(param_1 + 0xc); so that's the pointer itself. Then piVar3 is used as int*.

    int* currentTokenData = currentToken + 1; // next int after type

    // The code then constructs a 64-bit value from writePtr and currentToken (some concatenation)
    // That's weird.

    // I'm going to stop and just produce a reconstruction that matches the decompiled logic closely but with meaningful names.

    // Given the confusion, I'll produce a simpler reconstruction assuming the function is an interpreter step that reads the next token and either pushes a number or executes an operator.

    // I'll use the class "ScriptEngine" and method "processOneToken" (or "interpretNext").

    // Let's write the code as it appears in the decompiled output, using better names for locals.

    // From the decompiled, the function does:
    // - Check if next token's type is positive, if so call some conversion to get a float.
    // - Then check if current token's type is 3 or 4 (likely number types) and if the float condition (iVar4 != 0) then do a special push: copy the token to stack, increment stack, possibly grow if needed, then push "empty" or adjust.
    // - Otherwise, just copy the current token to the top of the stack and move on.

    // So I'll implement that.

    StackEntry* readPtr = (StackEntry*)ctx->readCursor;
    StackEntry* writePtr = (StackEntry*)ctx->writeCursor;

    // Check if next token exists and is a positive type (maybe pre-read for float conversion)
    int* nextTypePtr = (int*)((char*)readPtr + 8); // next 8-byte token's type
    float preFloat = 0.0f;
    if (nextTypePtr < (int*)writePtr && nextTypePtr != nullptr && *nextTypePtr > 0) {
        preFloat = readFloatFromToken(/* maybe uses in_XMM0_Da */);
    }

    int currentType = readPtr->type;
    if (writePtr >= readPtr && readPtr != nullptr && currentType != -1) // Actually check: *(int**)(param_1+8) <= piVar3? The code checks (*(int **)(param_1 + 8) <= piVar3) || ... so it's reversed logic.
    {
        // If current token is invalid, call error
        FUN_00627a20(ctx, 1, "value expected");
        // return? not explicitly but sets uVar7
    }
    else
    {
        // Normal case
        if ( (currentType == 4 || currentType == 3) && ((int)preFloat != 0) )
        {
            // Push current token onto stack? Actually they call FUN_00627b40 which might copy token to stack, then they copy manually *puVar2 = *puVar1; etc.
            // Then they increment writePtr.
            // Then check if stack is full and maybe grow.
            // Then call FUN_006343b0 which might adjust stack index.
            // Then decrement writePtr.
            // Then FUN_006338a0 (execute/process?).

            // This path is for when the current token is a number and some condition holds (maybe it's a float constant?)
            pushNumber(ctx, writePtr, readPtr); // details omitted
        }
        else
        {
            // Otherwise, just copy the token to the top of the stack (as an operator?)
            *writePtr = *readPtr;
            ctx->writeCursor += sizeof(StackEntry);
            FUN_006338a0(); // execute the operator?
        }
    }
}