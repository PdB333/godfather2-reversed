// FUNC_NAME: SomeClass::initializeSomething
void SomeClass::initializeSomething(uint32 param_1)
{
    // local_c is an array of 4 bytes (unused)
    uint8 unusedBuffer[4];
    
    // local_8 points to LAB_0062b6b0 (likely a vtable or function pointer table)
    void* vtablePtr = (void*)0x0062b6b0;
    
    // Call initialization routine
    FUN_006372d0();
    
    // Call setup function with param_1, 0, and unused buffer
    FUN_006371a0(param_1, 0, unusedBuffer);
    
    return;
}