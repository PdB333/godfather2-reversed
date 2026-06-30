// FUNC_NAME: EA::Assert::reportAssertionFailure
// Address: 0x0059c140
// Reconstructed assertion failure handler for EA's debug policy.
// When conditionResult is false (0), it logs the assertion info and may trigger a breakpoint.

void EA::Assert::reportAssertionFailure(char conditionResult)
{
    int *threadLocalInfo;
    code *int3Handler;
    uint flags;
    int fsOffset; // from FS segment register
    const char *expressionText;
    const char *sourceFile;
    int lineNumber;
    int policyFlags;
    char *assertionFlagPtr;

    // If condition is true (non-zero), do nothing
    if (conditionResult != '\0') {
        return;
    }

    // Set up assertion context: expression, file, line, policy flags
    expressionText = "expression";
    sourceFile = "c:\\packages001_pc\\apt\\0.19.optimized\\source\\apt\\ea/string/default_policy.h";
    lineNumber = 0x47; // line 71
    policyFlags = 2;

    // Pointer to a global assertion flag (DAT_01128f0a), likely controls whether assertion triggers
    assertionFlagPtr = &DAT_01128f0a;

    // Check if assertions are globally enabled
    if (*assertionFlagPtr != '\0') {
        // Get thread-local storage info (FS:[0x2c] is pointer to TIB, then offset 0x30 gives something)
        threadLocalInfo = *(int **)(**(int **)(fsOffset + 0x2c) + 0x30);

        // Set flags and potentially disable further assertions
        flags = 1;
        if (((threadLocalInfo == (int *)0x0) ||
            (flags = (**(code **)(*threadLocalInfo + 8))(&expressionText, "expression"),
             assertionFlagPtr != (char *)0x0)) &&
           ((flags & 2) != 0)) {
            *assertionFlagPtr = 0; // Disable assertion flag
        }

        // Check if we should trigger a breakpoint (int 3)
        if (((threadLocalInfo != (int *)0x0) || (policyFlags != 4)) &&
           (((flags & 1) != 0 || ((policyFlags == 0) || (policyFlags == 1))))) {
            int3Handler = (code *)swi(3);
            (*int3Handler)(); // Actually trigger breakpoint
            return;
        }
        return;
    }
    return;
}