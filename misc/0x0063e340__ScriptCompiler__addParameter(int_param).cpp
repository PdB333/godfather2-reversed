// FUNC_NAME: ScriptCompiler::addParameter(int param)
void ScriptCompiler::addParameter(int param)
{
    // +0x1c: pointer to ParserState structure
    ParserState* state = *(ParserState**)(this + 0x1c);
    beginParameter();
    
    // Parameter count check (max 100)
    if (state->parameterCount > 100) {
        int error = formatString("too many %s (limit=%d)", "parameters", 100);
        outputError(error);
    }
    
    // +0x45: store parameter index (count) in bytecode buffer
    *((char*)(state->bytecodeBuffer) + 0x45) = (char)state->parameterCount;
    // +0x46: store parameter type/flag
    *((char*)(state->bytecodeBuffer) + 0x46) = (char)param;
    
    if (param != 0) {
        emitOperator();
    }
    
    char* buffer = state->bytecodeBuffer;
    int newPosition = state->currentPosition + state->parameterCount;
    int originalCount = state->parameterCount; // saved before potential reassignment
    
    // Complexity tracking: byte at +0x47
    if ((int)(unsigned char)*(buffer + 0x47) < newPosition) {
        if (newPosition > 249) {
            long long result = outputError("function or expression too complex");
            int dummy = (int)(result >> 32); // unused, just to match Ghidra output
            // fall through
        }
        *(char*)(buffer + 0x47) = (char)newPosition;
    }
    
    // Advance current position
    state->currentPosition = state->currentPosition + originalCount;
}