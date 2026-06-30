// FUNC_NAME: pushToGlobalStack
void pushToGlobalStack(uint32_t value)
{
    // DAT_01206880 is a pointer to a global stack structure.
    // Offset +0x14 contains a pointer to the current write position (stack top).
    int *stackPtr = *(int **)(DAT_01206880 + 0x14);
    
    // Push a constant vtable/descriptor pointer onto the stack.
    *(uint32_t *)stackPtr = (uint32_t)&PTR_LAB_01126c80;  // +0x0
    stackPtr = (int *)((char *)stackPtr + 4);
    
    // Push the provided value onto the stack.
    *(uint32_t *)stackPtr = value;
    stackPtr = (int *)((char *)stackPtr + 4);
    
    // Update the global stack pointer to the new position.
    *(int **)(DAT_01206880 + 0x14) = stackPtr;
}