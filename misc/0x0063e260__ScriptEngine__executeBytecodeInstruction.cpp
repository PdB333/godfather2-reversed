// FUNC_NAME: ScriptEngine::executeBytecodeInstruction
// Address: 0x0063e260
// Role: Handles bytecode instruction execution in the EARS scripting engine.
// Processes opcode 0xc (arithmetic/stack operation) and other opcodes.
// Updates expression depth limit and manages instruction pointer.

void __thiscall ScriptEngine::executeBytecodeInstruction(
    int thisPtr, int instructionDelta, int baseOffset) {
    // piVar4 = pointer to stack context from this+0x1c
    int* context = *(int**)(thisPtr + 0x1c);
    // instructionDelta = relative offset computed by caller (instructionDelta = instructionDelta - baseOffset)
    instructionDelta -= baseOffset;
    // currentInstr is passed in EAX, pointing to the current bytecode instruction (opcode + operands)
    int* currentInstr = (int*)in_EAX;

    if (*currentInstr == 0xc) {
        // Opcode 0xc: special arithmetic/stack op
        int adjustedDelta = instructionDelta + 1;
        if (adjustedDelta < 1) {
            adjustedDelta = 0;
        } else {
            int bytecodeBase = *context; // base of bytecode array
            int newDepth = context[9] + instructionDelta; // context[9] = instruction pointer or stack top
            if ((int)(uint)*(byte*)(bytecodeBase + 0x47) < newDepth) {
                if (0xf9 < newDepth) {
                    // Expression too complex, error
                    context = (int*)context[3]; // alternate context?
                    uint* errorStr = FUN_00638b80("function or expression too complex");
                    // update in_EAX and bytecodeBase from error string? (likely unused)
                    currentInstr = (int*)errorStr;
                    newDepth = (int)((ulonglong)errorStr >> 0x20);
                    // Update the depth limit anyway
                }
                // Update expression depth limit at bytecodeBase+0x47
                *(char*)(bytecodeBase + 0x47) = (char)newDepth;
            }
            // Advance instruction pointer
            context[9] += instructionDelta;
        }

        if (*currentInstr == 0xc) {
            // Modify jump offset in instruction table
            uint* jumpTableEntry = (uint*)(*(int*)(*context + 0xc) + currentInstr[1] * 4);
            *jumpTableEntry ^= ((adjustedDelta + 1) * 0x40 ^ *jumpTableEntry) & 0x7fc0;
            if (adjustedDelta == 1) {
                // Convert to opcode 0xb with next byte as operand
                *currentInstr = 0xb;
                currentInstr[1] = (int)*(char*)(*(int*)(*context + 0xc) + 3 + currentInstr[1] * 4);
                return;
            }
        }
    } else {
        // Opcode is not 0xc
        if (*currentInstr != 0) {
            // Process other valid opcodes
            FUN_00642ec0(); // execute default opcode handler
        }
        if (0 < instructionDelta) {
            int bytecodeBase = *context;
            int newDepth = context[9] + instructionDelta;
            if ((int)(uint)*(byte*)(bytecodeBase + 0x47) < newDepth) {
                if (0xf9 < newDepth) {
                    context = (int*)context[3];
                    FUN_00638b80("function or expression too complex");
                    newDepth = (int)((ulonglong)errorStr >> 0x20);
                    bytecodeBase = (int)errorStr;
                }
                *(char*)(bytecodeBase + 0x47) = (char)newDepth;
            }
            context[9] += instructionDelta;
            // Advance bytecode stream
            FUN_00642420(instructionDelta);
        }
    }
    return;
}