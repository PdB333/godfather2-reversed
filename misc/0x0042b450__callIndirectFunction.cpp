// FUNC_NAME: callIndirectFunction
void callIndirectFunction(void)
{
    // Thunk: calls function pointer stored at address 0x0110ac0c
    // Original target function: 0x0042a9a0
    void (*funcPtr)(void) = *(void (**)(void))0x0110ac0c;
    funcPtr();
    return;
}