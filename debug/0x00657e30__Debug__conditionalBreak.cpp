// FUNC_NAME: Debug::conditionalBreak

void Debug::conditionalBreak(const char* conditionString)
{
    // If the condition string is non-empty, immediately trigger debug break
    if (conditionString && *conditionString != '\0') {
        Debug::breakHandler();
        return;
    }

    // If debug mode is disabled and the current tick count hasn't reached the limit, skip
    if (!g_debugModeEnabled && g_debugBreakCounter < g_debugBreakLimit) {
        return;
    }

    // Otherwise, trigger a breakpoint via software interrupt (swi 3)
    void (*breakHandler)() = reinterpret_cast<void (*)()>(swi(3)); // swi(3) returns a function pointer
    breakHandler();
}