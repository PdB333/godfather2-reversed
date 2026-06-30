//FUNC_NAME: aptAssertionHandler
// Address: 0x005abb50
// Role: Debug assertion handler for APT library (isMath() check)
void aptAssertionHandler() {
    // If assertion suppression is active, return early
    if (isAssertSuppressed()) {
        return;
    }

    const char* expression = "isMath()";
    const char* file = "c:\\packages001_pc\\apt\\0.19.optimized\\source\\apt\\_AptValue.h";
    int line = 0x125; // 293
    int severity = 2; // Assertion severity level
    char* debugFlag = &DAT_01128fd1; // Global debug flag (likely enables breakpoints)

    if (*debugFlag != 0) {
        // Access thread-local storage (FS:[0x2c] -> TLS pointer)
        int* tlsData = *(int**)(*(int**)(__readfsdword(0x2c)) + 0x30);
        uint flags = 1;

        // Check if TLS data exists and call a debug callback
        if ((tlsData == nullptr) ||
            (flags = (**(code**)(*tlsData + 8))(&expression, "isMath()"), debugFlag != nullptr)) {
            // If callback returned flags with bit 1 set, clear the debug flag
            if ((flags & 2) != 0) {
                *debugFlag = 0;
            }
        }

        // Trigger breakpoint if:
        // - TLS data exists OR severity is not 4 (fatal)
        // - AND (flags bit 0 set OR severity is 0 or 1)
        if ((tlsData != nullptr) || (severity != 4)) {
            if (((flags & 1) != 0) || (severity == 0 || severity == 1)) {
                __debugbreak(); // swi(3) - software breakpoint
                return;
            }
        }
    }
}