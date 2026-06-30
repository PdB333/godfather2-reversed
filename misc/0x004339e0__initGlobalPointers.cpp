// FUNC_NAME: initGlobalPointers
// Address: 0x004339e0
// Role: Initializes global function pointers and data values (likely EARS engine initialization)

void initGlobalPointers(void* ptr1, void* ptr2, uint32_t value)
{
    // Global function pointer set 1 (duplicated)
    g_funcPtrA = ptr1;   // +0x0110ac14
    g_funcPtrB = ptr1;   // +0x0110ac1c

    // Global function pointer set 2 (duplicated)
    g_funcPtrC = ptr2;   // +0x0110ac18
    g_funcPtrD = ptr2;   // +0x0110ac20

    // Global data values (duplicated)
    g_dataValA = value;  // +0x0110ac24
    g_dataValB = value;  // +0x0110ac28
}