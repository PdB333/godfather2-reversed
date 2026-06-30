// FUNC_NAME: ScriptCompiler::emitPushConstant
void __fastcall ScriptCompiler::emitPushConstant(int param_1)
{
    // This function appears to emit a "push constant" instruction into the bytecode stream.
    // param_1 is likely the constant value or opcode to push.
    // The class instance (this) is passed in EDI per EA convention.

    // Get the compiler context pointer (offset 0x1C from this)
    int* context = *(int**)(this + 0x1C); // +0x1C: pointer to current compile context

    // Allocate or get a symbol/object for param_1 (offset 0x0)
    int symbol = FUN_0063dd40(param_1, 0);
    FUN_0063de90(symbol); // Possibly finalize/register symbol

    int* codeBuffer = (int*)*context; // Pointer to code buffer start
    int depth = context[9]; // Current nesting depth, offset 0x24 (= 9*4)
    int newDepth = depth + 1;

    // Check depth against maximum allowed (at offset 0x47 in codeBuffer)
    if ((int)(uint)*(byte*)((int)codeBuffer + 0x47) < newDepth)
    {
        // Depth exceeded – if > 249, report error
        if (0xF9 < newDepth)
        {
            // Switch to error context? (context[3] may be a fallback context)
            context = (int*)context[3]; // +0x0C: alternative context
            int error = FUN_00638b80("function or expression too complex");
            // Note: the original code discards error and uses extraout_ECX
            codeBuffer = (int*)*context; // reassign from new context
        }
        // Update the max depth byte
        *(char*)((int)codeBuffer + 0x47) = (char)newDepth;
    }

    // Increment depth counter
    context[9] = newDepth;

    // Re-fetch context pointer (unclear why, but matches original)
    int* context2 = *(int**)(this + 0x1C);
    context2[0xD]++; // Increment instruction index (offset 0x34 = 0xD*4)

    // Emit instruction: store something into the instruction stream
    // Instruction stream is at (*context2 + 0x18) as an array of 12-byte entries.
    // Index = context2[ context2[0xD] + 0xAD ] (note: 0xAD is +0x2B4 words? Check offsets)
    int instrIndex = context2[ context2[0xD] + 0xAD ]; // Likely a mapping to an instruction slot
    int* instrBase = (int*)(*(int*)(*context2 + 0x18) + 4); // Skip first dword? +4 for field offset
    instrBase[instrIndex * 3] = context2[6]; // Write value from context[6] (offset 0x18)

    // Build a temp string for error/logging? Using a 20-byte buffer
    char tempBuffer[20];
    FUN_0063f080(tempBuffer, 0, *(int*)(this + 4)); // +0x04: some string/name
    // Emit the constant opcode (5) using another function
    int opCode = 5;
    FUN_00643090(&opCode); // Probably writes opcode to current position

    // Second emit using possibly updated context (after error path)
    instrIndex = context[ context[0xD] + 0xAD ];
    instrBase = (int*)(*(int*)(*context + 0x18) + 4);
    instrBase[instrIndex * 3] = context[6]; // Write same value field
}