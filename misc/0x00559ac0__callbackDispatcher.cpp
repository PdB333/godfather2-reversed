// FUNC_NAME: callbackDispatcher
void callbackDispatcher(uint32_t arg0, uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4)
{
    // 0x00557e20 - likely a singleton getter or initialization routine
    FUN_00557e20();
    // 0x00c09ee0 - main handler that processes the forwarded parameters
    FUN_00c09ee0(arg0, arg1, arg2, arg3, arg4);
}