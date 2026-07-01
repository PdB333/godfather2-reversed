// FUNC_NAME: assertionFailureHandler
// Function address: 0x005a73a0
// Role: Assertion failure handler for APT library (AptValue.h). Called when an assertion like isInteger() fails.
// Parameters inferred from stack usage: expression string, file path, line number, flags, pointer to global assertion enabled flag.
void assertionFailureHandler(const char* expression, const char* file, int line, int flags, bool* enabledFlag)
{
    // Check if assertions are globally enabled (e.g., debug build)
    if (isAssertionEnabled()) {
        return;
    }

    // Set up assertion message parameters (these would normally be passed by the macro)
    expression = "isInteger()";
    file = "c:\\packages001_pc\\apt\\0.19.optimized\\source\\apt\\_AptValue.h";
    line = 0xc3; // 195
    flags = 2;
    enabledFlag = &DAT_01128fa7; // Global assertion enabled flag

    // If assertion handling is enabled globally
    if (*enabledFlag != '\0') {
        // Access thread-local storage (FS:0x2C -> TLS array, then offset 0x30)
        int* tlsPtr = *(int**)(*(int*)(__readfsdword(0x2C)) + 0x30);
        uint uVar4 = 1;

        // Check if TLS pointer is valid and call a debugger/exception callback
        if ((tlsPtr == (int*)0x0) ||
            (uVar4 = (**(code**)(*tlsPtr + 8))(&expression, "isInteger()"), enabledFlag != (bool*)0x0))
        {
            if ((uVar4 & 2) != 0) {
                *enabledFlag = false; // Disable further assertions?
            }
        }

        // Additional checks to trigger a debug breakpoint (int 3)
        if ((tlsPtr != (int*)0x0) || (flags != 4)) {
            if (((uVar4 & 1) != 0) || ((flags == 0) || (flags == 1))) {
                // Trigger software interrupt (debug breakpoint)
                __debugbreak();
                return;
            }
        }
    }
}