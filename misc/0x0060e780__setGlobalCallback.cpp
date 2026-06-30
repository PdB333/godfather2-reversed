// FUNC_NAME: setGlobalCallback
// Address: 0x0060e780
// Sets a global function pointer, returns the previous value. If new is null, resets to default handler (FUN_0060e730).

typedef void (*CallbackFunc)();

// Global function pointer at 0x00f15a3c
CallbackFunc g_globalCallback = nullptr;

CallbackFunc setGlobalCallback(CallbackFunc newCallback)
{
    CallbackFunc oldCallback = g_globalCallback;
    g_globalCallback = newCallback;
    if (newCallback == nullptr)
    {
        g_globalCallback = (CallbackFunc)0x0060e730; // Default callback function
    }
    return oldCallback;
}