// FUNC_NAME: setGlobalFunctionPointer
void setGlobalFunctionPointer(void* newFuncPtr)
{
    // Sets the global function pointer at 0x0110ac0c to the given address
    // This is likely used to register a callback or hook into engine processing
    gEngineCallback = newFuncPtr;
}