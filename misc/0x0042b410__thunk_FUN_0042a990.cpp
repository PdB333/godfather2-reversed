// FUNC_NAME: thunk_FUN_0042a990

// Global function pointer used for dynamic dispatch (likely a thunk or hook)
typedef void (*FunctionPtr)(void);
extern FunctionPtr PTR_FUN_0110ac08;

void thunk_FUN_0042a990(void)
{
    // Indirect jump through the global pointer; calls the target function with no arguments
    PTR_FUN_0110ac08();
}