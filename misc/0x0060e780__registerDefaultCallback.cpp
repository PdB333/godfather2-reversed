// FUNC_NAME: registerDefaultCallback
// Address: 0x0060e780
// Replaces a global function pointer with a new handler, returning the old one.
// If null is passed, restores the default handler (FUN_0060e730).
// This pattern is typical for hooking or callback registration systems 
// used in the EARS engine (e.g., networking event dispatchers).

typedef void (*CallbackFunc)(); // Function pointer type

static CallbackFunc g_globalCallback = FUN_0060e730; // +0x0 (global at 0x00f15a3c)

CallbackFunc registerDefaultCallback(CallbackFunc newCallback)
{
    CallbackFunc oldCallback = g_globalCallback;
    g_globalCallback = newCallback;
    if (newCallback == nullptr)
    {
        g_globalCallback = FUN_0060e730; // Default fallback
    }
    return oldCallback;
}