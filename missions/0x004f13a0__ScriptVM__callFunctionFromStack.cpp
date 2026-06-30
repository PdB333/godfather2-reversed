// FUNC_NAME: ScriptVM::callFunctionFromStack
void ScriptVM::callFunctionFromStack(void* thisPtr, void (*func)(uint32_t, uint32_t, uint64_t, uint32_t, uint32_t, uint32_t))
{
    // thisPtr + 0x18 points to a stack pointer (argument buffer)
    uint32_t* stackPtr = *(uint32_t**)((char*)thisPtr + 0x18);
    
    // First argument is read directly from the current stack pointer
    uint32_t arg0 = *stackPtr;
    
    // Align the stack pointer to the next 4-byte boundary (round up)
    uint32_t* alignedPtr = (uint32_t*)(((uint32_t)stackPtr + 7) & 0xFFFFFFFC);
    *(uint32_t**)((char*)thisPtr + 0x18) = alignedPtr;
    
    // Read remaining arguments from the aligned buffer
    uint32_t arg1 = *alignedPtr;
    *(uint32_t**)((char*)thisPtr + 0x18) = alignedPtr + 1;
    
    uint64_t arg2 = *(uint64_t*)(alignedPtr + 1);
    uint32_t arg3 = *(alignedPtr + 3);
    *(uint32_t**)((char*)thisPtr + 0x18) = alignedPtr + 4;
    
    uint64_t temp = *(uint64_t*)(alignedPtr + 4);
    uint32_t arg4 = (uint32_t)temp;
    uint32_t arg5 = (uint32_t)(temp >> 32);
    *(uint32_t**)((char*)thisPtr + 0x18) = alignedPtr + 6;
    
    // Call the function pointer with the extracted arguments
    func(arg0, arg1, arg2, arg3, arg4, arg5);
}