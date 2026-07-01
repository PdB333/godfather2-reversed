// FUNC_NAME: AptValue::assertIsSound

void AptValue::assertIsSound()
{
    // Check if assertion monitoring is suppressed (e.g., during initialization)
    if (FUN_005a8030() != 0) {
        return;
    }

    // Assertion parameters: expression "isSound()", file "_AptValue.h", line 0x10a, level 2
    const char* expression = "isSound()";
    const char* fileName = "c:\\packages001_pc\\apt\\0.19.optimized\\source\\apt\\_AptValue.h";
    int lineNumber = 0x10a; // 266
    int severity = 2; // Error level
    char* assertFlag = &DAT_01128faf; // Global flag to enable/disable assertions

    if (*assertFlag != 0) {
        // Access thread-local storage from the FS segment
        // unaff_FS_OFFSET is the thread environment block (TEB) offset
        int* tebPtr = *(int**)(*(int**)(*(uint*)__readfsdword(0x2c) + 0x30));
        uint flags = 1;
        if (tebPtr == 0) {
            flags = 0;
        } else {
            // Call a function pointer to perform assertion output/logging
            flags = (**(code**)(*tebPtr + 8))(&expression, "isSound()");
        }

        // If the assertion condition (in flags) requires a breakpoint, trigger it
        if ((flags & 2) != 0) {
            *assertFlag = 0; // Clear flag to prevent re-entry
        }

        // Additional checks for forced breakpoints
        if (tebPtr != 0 || severity == 4) {
            if ((flags & 1) != 0 || (severity == 0 || severity == 1)) {
                // Trigger debug breakpoint (int 3)
                __debugbreak();
                return;
            }
        }
    }
}