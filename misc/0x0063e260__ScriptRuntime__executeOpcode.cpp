// FUNC_NAME: ScriptRuntime::executeOpcode
// Address: 0x0063e260
// Role: Execute a single opcode in the script expression evaluator (handles loop/control structures)
void __thiscall ScriptRuntime::executeOpcode(int thisPtr, int delta, int limit)
{
    // +0x1c: pointer to runtime state structure (RuntimeState)
    RuntimeState* state = *(RuntimeState**)(thisPtr + 0x1c);
    
    // current opcode is passed in EAX (not in standard calling convention, but used by this game)
    int* currentOpcode; // implicit parameter (register EAX)
    
    // compute adjusted delta (difference between delta and limit)
    delta = delta - limit;
    
    if (*currentOpcode == 0xC)  // opcode for "for" loop initialization?
    {
        int adjusted = delta + 1;
        if (adjusted < 1)
        {
            adjusted = 0;
        }
        else
        {
            // state->baseBlock (state[0]) points to a memory block
            int* baseBlock = (int*)state->baseBlock;  // state[0]
            int newDepth = state->depthCounter + delta;  // state[9]
            
            // Check if newDepth exceeds the maximum allowed depth (byte at baseBlock+0x47)
            if ((int)(unsigned char)*(char*)(baseBlock + 0x47) < newDepth)
            {
                if (newDepth > 0xF9)
                {
                    // Too complex: set error handler pointer and call error routine
                    state = (RuntimeState*)state->errorHandler;  // state[3]
                    FUN_00638b80("function or expression too complex");
                    // The return value of the error function may modify currentOpcode and baseBlock
                    // (compiler generated extra assignments)
                }
                *(char*)(baseBlock + 0x47) = (char)newDepth;  // update max depth
            }
            state->depthCounter += delta;  // increment depth counter
        }
        
        if (*currentOpcode == 0xC)  // still the same opcode after potential error handler?
        {
            // Access a jump table at baseBlock+0xC, indexed by the opcode's operand
            int* jumpTable = *(int**)(state->baseBlock + 0xC);
            uint* target = (uint*)(jumpTable + currentOpcode[1] * 4);
            
            // Modify jump offset: store a relative offset (11-bit field)
            *target = *target ^ (((adjusted + 1) * 0x40) ^ *target) & 0x7FC0;
            
            if (adjusted == 1)  // delta was 0? (adjusted = delta+1 == 1)
            {
                // Change opcode to 0xB (loop condition check?) and load next operand
                *currentOpcode = 0xB;
                currentOpcode[1] = (int)*(char*)(jumpTable + 3 + currentOpcode[1] * 4);
                return;
            }
        }
    }
    else
    {
        if (*currentOpcode != 0)
        {
            FUN_00642ec0();  // error: unknown opcode
        }
        
        if (delta > 0)
        {
            int* baseBlock = (int*)state->baseBlock;
            int newDepth = state->depthCounter + delta;
            
            // Check and update maximum depth (same as above)
            if ((int)(unsigned char)*(char*)(baseBlock + 0x47) < newDepth)
            {
                if (newDepth > 0xF9)
                {
                    state = (RuntimeState*)state->errorHandler;
                    FUN_00638b80("function or expression too complex");
                }
                *(char*)(baseBlock + 0x47) = (char)newDepth;
            }
            state->depthCounter += delta;
            FUN_00642420(delta);  // allocate or grow memory for expression stack
        }
    }
    return;
}