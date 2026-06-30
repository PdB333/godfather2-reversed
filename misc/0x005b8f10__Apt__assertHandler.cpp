// FUNC_NAME: Apt::assertHandler
void Apt::assertHandler(const char* expr, const char* file, int line, int type, bool* conditionFlag)
{
    // Source: ..\source\Apt\AptInput.cpp, line 0x439 (1081)
    // EA assertion handler: if conditions are enabled and expression fails, trigger debug break.
    static const char* exprStr = &DAT_00e36da0; // Expression string table entry (e.g. "false")

    // Check if assertions are globally enabled (pointer at 0x01129140 must not be null/zero)
    if (!conditionFlag || *conditionFlag == false) {
        // Assertions disabled, return silently
        return;
    }

    // Get thread-local exception registration (used for structured exception handling)
    int* exceptionList = *(int**)(*(int**)(__readfsdword(0x2c)) + 0x30);
    unsigned int flags = 1;

    // If no exception handler or if the expression result is falsy, clear the condition flag
    if ((exceptionList == nullptr) ||
        ((*(code**)(*exceptionList + 8))(&exprStr, &DAT_00e36da0), conditionFlag != nullptr))
    {
        if ((flags & 2) != 0) {
            // Mark condition as false to prevent re-entry
            *conditionFlag = false;
        }
    }

    // Trigger debug break if:
    // - There is an exception handler OR the type is not 4 (ignore?)
    // - AND (flags & 1) is set, or type is 0 or 1 (continue vs break)
    if ((exceptionList != nullptr) || (type != 4)) {
        if (((flags & 1) != 0) || ((type == 0) || (type == 1))) {
            __debugbreak();
            return;
        }
    }

    return;
}