// FUNC_NAME: dispatchGlobalCallback
void dispatchGlobalCallback(void)
{
    // Call global function pointer (stored at 0x0119caf0) with command 8 and parameter 0
    (*g_engineCallbackPtr)(8, 0);
}