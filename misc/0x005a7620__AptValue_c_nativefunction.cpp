// Xbox PDB: AptValue::c_nativefunction
// FUNC_NAME: AptAssertHandler
void AptAssertHandler(void)
{
    int *exceptionInfo;
    code *handler;
    char enabled;
    uint result;
    int fsBase;
    char *exprStr; // expression string
    char *fileStr; // file path
    undefined4 lineNum; // line number
    int severity; // assertion severity level (2 = warning, etc.)
    undefined1 *flagPtr; // pointer to global flag

    // Check if debug shell is active; if so, skip display
    enabled = isDebugActive();
    if (enabled != '\0') {
        return;
    }

    // Assertion data set by the macro
    exprStr = "isNativeFunction()";
    fileStr = "c:\\packages001_pc\\apt\\0.19.optimized\\source\\apt\\_AptValue.h";
    lineNum = 0xe6; // 230
    severity = 2; // severity level (e.g., ASSERT, ASSERT_WARNING)
    flagPtr = &DAT_01128fab; // global assertion flag

    // If the global flag is set, perform error handling
    if (DAT_01128fab != '\0') {
        // Access thread-local storage for exception registration
        // FS:[0x2C] points to the thread environment block (TEB)
        // +0x30 gives the exception handler list (_EXCEPTION_REGISTRATION_RECORD)
        exceptionInfo = *(int **)(**(int **)(fsBase + 0x2c) + 0x30);
        result = 1;
        if (((exceptionInfo == (int *)0x0) ||
            (result = (**(code **)(*exceptionInfo + 8))(&exprStr,"isNativeFunction()"),
            flagPtr != (undefined1 *)0x0)) && ((result & 2) != 0)) {
            // If the exception handler is present and conditions met, clear the flag
            *flagPtr = 0;
        }
        if (((exceptionInfo != (int *)0x0) || (severity != 4)) &&
           (((result & 1) != 0 || ((severity == 0 || (severity == 1)))))) {
            // Trigger a breakpoint (int 3) for debugging
            handler = (code *)swi(3);
            (*handler)();
            return;
        }
        return;
    }
    return;
}