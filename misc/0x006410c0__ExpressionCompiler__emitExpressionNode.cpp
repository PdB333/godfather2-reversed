// FUNC_NAME: ExpressionCompiler::emitExpressionNode
void __thiscall ExpressionCompiler::emitExpressionNode(int thisPtr)
{
    int *statePtr = *(int **)(thisPtr + 0x1c); // compiler state (offset +0x1c)
    int luaValue = luaGetStackTop(statePtr, 0);      // FUN_0063dd40
    luaPushStack(luaValue);                           // FUN_0063de90

    int *basePtr = (int *)*statePtr;                 // deref to get base memory block
    int currentDepth = statePtr[9];                   // offset 0x24
    int newDepth = currentDepth + 1;
    // local_28: opcode (5), local_24: depth, local_1c/local_18: -1
    int instructionHeader[4] = {5, newDepth, -1, -1};

    // Update max depth in the base header
    if ( *(unsigned char *)(basePtr + 0x47) < (unsigned int)newDepth )
    {
        if ( newDepth > 0xf9 )
        {
            luaError("function or expression too complex"); // FUN_00638b80
        }
        *(char *)(basePtr + 0x47) = (char)newDepth;
    }
    statePtr[9] = newDepth;

    // Increment instruction count
    statePtr[0xd]++; // offset 0x34 (+0xd*4)

    // Write first instruction: set code[index] to stored register value
    int *codeBase = *(int **)(*statePtr + 0x18); // code array pointer (offset 0x18 from base)
    int index = statePtr[statePtr[0xd] + 0xad]; // indexing via mapping table (offset 0x2b4)
    *(codeBase + 1 + index * 3) = statePtr[6];  // instruction operand = current register

    // Clear a temporary buffer (20 bytes)
    memset(local_14, 0, *(int *)(thisPtr + 4)); // FUN_0063f080, size from this+4
    // Initialize instruction node from the header
    constructInstruction(&instructionHeader[0]); // FUN_00643090

    // Write second instruction (same index, but after node init)
    *(codeBase + 1 + index * 3) = statePtr[6];
}