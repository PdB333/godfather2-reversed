//FUNC_NAME: AptValue::assertIsString
// Function address: 0x005a3a40
// Role: Debug assertion that the AptValue is a string type. Called from many places in APT UI system.
// File: c:\packages001_pc\apt\0.19.optimized\source\apt\_AptValue.h line 210

void AptValue::assertIsString()
{
    // Check if assertions are globally enabled
    if (isAssertEnabled()) {
        return;
    }

    const char* functionName = "isString()";
    const char* fileName = "c:\\packages001_pc\\apt\\0.19.optimized\\source\\apt\\_AptValue.h";
    uint32_t lineNumber = 0xd2; // 210
    int32_t assertFlags = 2; // Possibly severity or type
    uint8_t* assertFlagPtr = &g_assertEnabled; // DAT_01128f68

    if (g_assertEnabled != 0) {
        // Get thread-local storage for assert handling (FS segment offset)
        int* pThreadData = *(int**)(*(int**)(__readfsdword(0x2c)) + 0x30);
        uint32_t result = 1;

        if ((pThreadData == nullptr) ||
            (result = (**(code**)(*pThreadData + 8))(&functionName, "isString()"),
             assertFlagPtr != nullptr))
        {
            if ((result & 2) != 0) {
                *assertFlagPtr = 0; // Clear assert flag
            }
        }

        if ((pThreadData != nullptr) || (assertFlags != 4)) {
            if (((result & 1) != 0) || ((assertFlags == 0) || (assertFlags == 1))) {
                // Trigger debug breakpoint
                __debugbreak();
                return;
            }
        }
        return;
    }
    return;
}