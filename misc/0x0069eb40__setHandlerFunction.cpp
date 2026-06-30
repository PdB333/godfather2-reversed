// FUNC_NAME: setHandlerFunction
void setHandlerFunction(void)
{
    // Set global function pointer to the handler function at 0x0069eb00
    g_pfnHandler = &handlerFunction;  // DAT_0120545c = &LAB_0069eb00
    return;
}