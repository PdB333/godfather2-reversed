// FUNC_NAME: ScriptInterpreter::executeBytecodeSegment
void __thiscall ScriptInterpreter::executeBytecodeSegment(int *this, int bytecodeBase) {
    int tokenOffset;
    int instructionLen;
    
    // FUN_006a3840: find token index in bytecode for a specific pattern (DAT_00d5d604)
    tokenOffset = findToken(bytecodeBase, &DAT_00d5d604);
    if ((tokenOffset < 0) || (*(short *)(bytecodeBase + tokenOffset * 2) != 0x3c)) {
        // Token not found, or first token is not 0x3c -> fallback to virtual handler
        // Call virtual function at vtable+4 (likely handleUnrecognized or defaultAction)
        (**(code **)(*(int *)this[1] + 4))();
        return;
    }
    
    // FUN_006a37b0: get length of the instruction at this token position
    instructionLen = getInstructionLength(bytecodeBase + tokenOffset * 2);
    if (instructionLen != -1) {
        if (instructionLen != -2) {
            tokenOffset = tokenOffset + instructionLen;
        }
        // FUN_006a3c60: execute the instruction at the new offset
        int result = executeInstruction(bytecodeBase + tokenOffset * 2, this, *this != 0, tokenOffset);
        if (-1 < result) {
            return; // Success
        }
    }
    
    // FUN_006a38f0: handle error or skip to next segment
    handleScriptError(tokenOffset);
    return;
}