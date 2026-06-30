// FUNC_NAME: registerCallback
void registerCallback(void* param_1)
{
    // Global pointer to a manager structure (DAT_01206880)
    // Offset +0x14 holds a pointer to a stack pointer (int**)
    int** ppStack = *(int***)((char*)DAT_01206880 + 0x14);
    
    // Push a constant handler pointer (PTR_LAB_01126bb8) onto the stack
    *ppStack = (int*)&PTR_LAB_01126bb8;
    ppStack++; // advance stack pointer
    
    // Push the provided parameter onto the stack
    *ppStack = (int*)param_1;
    ppStack++; // advance stack pointer
    
    // Update the stored stack pointer in the manager
    *(int***)((char*)DAT_01206880 + 0x14) = ppStack;
}