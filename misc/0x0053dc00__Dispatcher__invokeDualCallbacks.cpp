// FUNC_NAME: Dispatcher::invokeDualCallbacks
void __fastcall Dispatcher::invokeDualCallbacks(void* thisPtr, int param2, int param3)
{
    // Global index into handler tables (0x0121bf30)
    int handlerIndex = *reinterpret_cast<int*>(0x0121bf30);

    // Base addresses of handler tables - each table has entries of size 0x1b (27 bytes)
    // Entry at offset 0: pointer to a callback (likely a function or object pointer)
    volatile int* handler1 = reinterpret_cast<int*>(0x01198ea8 + handlerIndex * 0x1b);
    if (*handler1 != 0) {
        // Calls a helper function with global context, the handler pointer, and the parameter
        FUN_0060add0(*reinterpret_cast<void**>(0x0121be9c), *handler1, param2);
    }

    volatile int* handler2 = reinterpret_cast<int*>(0x01198eac + handlerIndex * 0x1b);
    if (*handler2 != 0) {
        FUN_0060add0(*reinterpret_cast<void**>(0x0121be9c), *handler2, param3);
    }
}