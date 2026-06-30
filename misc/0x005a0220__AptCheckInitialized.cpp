// FUNC_NAME: AptCheckInitialized

void AptCheckInitialized(void)
{
    // Global: indicates if the Apt library has been initialized
    extern int g_bAptInitialized; // DAT_012055b0
    // Global: master switch for assertion handling (byte)
    extern bool g_bAssertEnabled; // DAT_01128f5a

    // If Apt is already initialized, skip assertion handling
    if (g_bAptInitialized != 0)
    {
        goto LAB_AptInitFallback;
    }

    // Prepare assertion context on stack
    const char* conditionStr = "bAptIsInitialized";        // Condition expression as string
    const char* sourceFile = "..\\source\\Apt\\Apt.cpp";   // Source file name
    int lineNumber = 0x33a;                                // Line number in source (826)
    int severity = 2;                                      // Assertion severity level
    bool* pAssertEnabled = &g_bAssertEnabled;              // Pointer to the assertion enable flag

    // If assertions are globally disabled, skip
    if (g_bAssertEnabled == false)
    {
        goto LAB_AptInitFallback;
    }

    // Retrieve assertion handler from thread-local storage
    // FS:[0x2C] points to the thread-local storage array
    void* tlsArray = *(void**)(__readfsdword(0x2C));
    // At offset 0x30 in the TLS array is a pointer to an assertion handler object
    // (EA's standard assertion infrastructure)
    AssertHandler* handler = *(AssertHandler**)((char*)tlsArray + 0x30);

    if (handler != nullptr)
    {
        // Call the handler's assert method (vtable entry at offset 8)
        // First parameter: pointer to a struct containing (conditionStr, sourceFile, line, severity, ...)
        // Second parameter: condition string again (for logging)
        uint handlerResult = handler->vtable->assert(&conditionStr, conditionStr);

        // If the handler indicates "disable further assertions" (bit 2), turn off assertions
        if ((handlerResult & 2) != 0)
        {
            *pAssertEnabled = false;
        }
    }

    // Trigger a debug break if appropriate:
    // - handler exists OR severity is not 4
    // - AND (handlerResult & 1) OR severity is 0 or 1
    if ((handler != nullptr || severity != 4) &&
        ((handlerResult & 1) != 0 || severity == 0 || severity == 1))
    {
        __debugbreak(); // int 3 (swi(3) in ARM disassembly)
    }

LAB_AptInitFallback:
    // Fallback function: likely initializes the Apt system or handles the assertion
    FUN_005a2500();
}