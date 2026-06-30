// FUNC_NAME: ScriptThread::pushCommand
void __fastcall ScriptThread::pushCommand(uint32_t arg)
{
    // Get per-thread context pointer from Thread Local Storage (FS:[0x2C] is EA EARS thread context pointer)
    ScriptThread* threadContext = *(ScriptThread**)(__readfsdword(0x2C));
    
    // Reset a flag at offset +0x28 (e.g., a "continue" or "abort" flag)
    threadContext->field_0x28 = 0;

    // Check condition at offset +0x34 (0 means script execution is active)
    if (threadContext->field_0x34 == 0)
    {
        // Global machine context (DAT_01206880) +0x14 holds a pointer to the script stack pointer variable
        int** stackPointerPtr = (int**)(g_scriptMachine + 0x14); // pointer to stack top pointer
        int* stackTop = *stackPointerPtr; // current top of stack (points to next free slot)

        // Write vtable pointer for the script opcode (PTR_LAB_0110b708 identifies the operation)
        *stackTop = (int)&SCRIPT_OPCODE_TABLE; // +0x0: vtable
        stackTop++; // advance

        // Write the argument (the command parameter)
        *stackTop = arg;
        stackTop++; // advance

        // Update the stack pointer
        *stackPointerPtr = stackTop;
    }
}