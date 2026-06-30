// FUNC_NAME: Debug::handleAssert
void __thiscall Debug::handleAssert(const char* conditionString) {
    // +0x00: conditionString (in EAX) - pointer to a string describing the assertion condition.
    // If the condition string is non-empty (assertion failed), log the error and return.
    if (*conditionString != '\0') {
        FUN_0065fab0(); // Likely Debug::logAssertionFailure or similar logging routine
        return;
    }
    // +0x00: g_debugAssertEnabled (DAT_01127d3c) - flag to enable/disable debug breakpoints
    // +0x00: g_debugAssertCounter (DAT_01127d38) - current assertion counter
    // +0x00: g_debugAssertMaxCounter (DAT_01205a6c) - threshold to suppress extra breaks
    // If debug assertions are disabled and the counter is below the max, skip breakpoint.
    if ((g_debugAssertEnabled == '\0') && (g_debugAssertCounter < g_debugAssertMaxCounter)) {
        return;
    }
    // Trigger software breakpoint (int 3) and optionally call a break handler.
    // In the original, swi(3) is used as a macro that may return a handler address; 
    // here we simulate with __debugbreak and a callback.
    __debugbreak();
    // After break, call break handler (if any). Assuming a global function pointer.
    if (g_debugBreakHandler != nullptr) {
        g_debugBreakHandler();
    }
}