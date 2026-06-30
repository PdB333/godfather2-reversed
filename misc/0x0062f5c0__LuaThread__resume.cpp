// FUNC_NAME: LuaThread::resume
// Function address: 0x0062f5c0
// Role: Resume execution of a Lua coroutine, passing a single integer argument.
// Returns number of results (as int) on success, or -1 on error.
// Offsets:
//   +0x08: m_pTop (pointer to current top of result stack, incremented by number of results)
//   +0x0c: m_pBase (pointer to base of result stack for this coroutine)

class LuaThread {
public:
    // Stack pointers (interpreted as 8‑byte aligned TValue slots)
    int* m_pTop;   // +0x08
    int* m_pBase;  // +0x0c

    // External helpers (must be implemented elsewhere)
    static bool checkStackReserve(int count);   // FUN_006254f0
    static void reportError(const char* msg);  // FUN_00627bd0
    static void pushValue(int value);           // FUN_00625540
    static int resume();                        // FUN_00636440

    // Resume this coroutine with one integer argument
    int resume(int arg);
};

int LuaThread::resume(int arg) {
    // Ensure there is room on the stack for the argument
    if (!checkStackReserve(1)) {
        reportError("too many arguments to resume");
    }

    // Push the argument onto the coroutine's stack
    pushValue(arg);

    // Attempt to resume the coroutine
    if (resume() != 0) {
        // Error occurred; push the error object and return -1
        pushValue(this);  // ??? This seems to push the coroutine itself?
        return -1;
    }

    // Success: calculate number of results from stack top and base
    int numResults = (m_pTop - m_pBase) / 8; // each result is 8 bytes
    return numResults;
}