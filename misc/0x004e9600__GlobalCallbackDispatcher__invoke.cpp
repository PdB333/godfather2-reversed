// FUNC_NAME: GlobalCallbackDispatcher::invoke
// Address: 0x004e9600
// Reads a function pointer from a global structure (offset 0x2c) and calls it with swapped parameters.
void __fastcall invokeGlobalCallback(void* param1, void* param2)
{
    // Global data at address 0x012234c4 (likely a singleton or manager instance)
    // Offset 0x2c stores a function pointer (code*)
    typedef void (__fastcall *Callback)(void*, void*);
    Callback* pCallback = reinterpret_cast<Callback*>(0x012234c4 + 0x2c);
    if (pCallback != nullptr && *pCallback != nullptr)
    {
        // Note: parameters are swapped when calling the callback
        (*pCallback)(param2, param1);
    }
}