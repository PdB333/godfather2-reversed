// FUNC_NAME: SpinWaitForCondition
void SpinWaitForCondition(int synchronizationFlag, int currentValue, int expectedFlagValue, int expectedValue) {
    // Function address: 0x00485130
    // Spin-wait until currentValue == expectedValue.
    // If synchronizationFlag is 0 or not equal to expectedFlagValue, call debug/log.
    // Each iteration yields and increments a global debug counter (pointed by unaff_EDI in original disasm).
    extern int g_debugSpinWaitCounter; // global counter incremented per iteration

    while (true) {
        // Check if synchronization flag matches expected; if mismatch or zero, report error
        if (synchronizationFlag == 0 || synchronizationFlag != expectedFlagValue) {
            // FUN_00b97aea — likely a debug assertion or log output
            debugAssertOrLog();
        }

        // Exit when current value reaches expected
        if (currentValue == expectedValue)
            break;

        // Increment debug counter
        g_debugSpinWaitCounter++;

        // Yield CPU to other threads (FUN_00484fb0)
        yieldProcessor();
    }
}