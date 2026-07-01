// FUNC_NAME: AptValue::assertIsScriptFunction
void AptValue::assertIsScriptFunction(void)
{
    // Check if assertions are disabled (e.g., retail build)
    if (isAssertDisabled()) {
        return;
    }

    // Assert context: file, function name, line, debug level
    const char* assertFunc = "isScriptFunction()";
    const char* assertFile = "c:\\packages001_pc\\apt\\0.19.optimized\\source\\apt\\_AptValue.h";
    uint assertLine = 0xDC; // 220
    int assertLevel = 2;     // Debug level
    gDebugAssertActive = &DAT_01128f69; // Global flag to enable/disable debug output

    // If debug assertion output is globally enabled
    if (*gDebugAssertActive != '\0') {
        // Access thread-local storage via FS segment (SEH chain)
        int* pTls = *(int**)(*(int**)(__readfsdword(0x2C)) + 0x30);
        uint flags = 1;

        if ((pTls == (int*)0x0) ||
            (flags = (**(code**)(*pTls + 8))(&assertFunc, "isScriptFunction()"),
             gDebugAssertActive != (undefined1*)0x0)) {
            if ((flags & 2) != 0) {
                *gDebugAssertActive = 0; // Suppress further assertions
            }
        }

        if ((pTls != (int*)0x0) || (assertLevel != 4)) {
            if (((flags & 1) != 0) || (assertLevel == 0) || (assertLevel == 1)) {
                // Trigger debug break (int 3)
                __debugbreak();
                return;
            }
        }
        return;
    }
    return;
}