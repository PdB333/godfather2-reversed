// FUNC_NAME: invokeProtectedCode
void invokeProtectedCode(void* param_1, void* param_2)
{
    // SEH registration block (prev, handler, scopy)
    int exceptionReg[3] = { 0, 0, 0 };
    // Exception handler function pointer (filter)
    void (*exceptFilter)(int) = nullptr;

    // Install exception handler with global data (likely exception handling table)
    setExceptionHandler(exceptionReg, &DAT_00e3266c, param_2);

    // Execute the guarded function (first parameter)
    executeActualFunction(param_1);

    // Uninstall exception handler
    restoreExceptionHandler(exceptionReg);

    // If an exception was raised (exceptionReg[0] != 0), call the filter with the exception code
    if (exceptionReg[0] != 0)
    {
        exceptFilter(exceptionReg[0]);
    }
}