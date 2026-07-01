// Xbox PDB: void __cdecl luaD_call(struct lua_State *,struct lua_TObject *,int)
// FUNC_NAME: CoroutineScheduler::executeCoroutine
class CoroutineScheduler {
public:
    // Coroutine system: manages cooperative multitasking via fiber-like coroutines
    // Each coroutine has a context struct with:
    // +0x10: pointer to a state machine (or scheduler internal object) with fields at +0x20 and +0x24 (pending/processed counts)
    // +0x2e: uint16_t recursion depth counter (protects against C stack overflow)

    // Executes a coroutine with the given argument.
    // This is the core dispatch loop for cooperative tasks.
    void __thiscall executeCoroutine(void* coroutine, void* arg);
};

// Offsets within the coroutine context (assumed to be a pointer to a Coroutine::Context struct)
// +0x10: pointer to some state/machine object (let's call it m_stateMachine)
// +0x2e: uint16_t depth
// The state machine object (at +0x10) itself has:
// +0x20: uint32_t pendingCount
// +0x24: uint32_t processedCount

// Forward declarations of called functions (stubs from the module)
void __cdecl reportStackOverflow(void* coroutine, const char* msg);              // FUN_00633920
int  __cdecl processEvent(void* arg);                                            // FUN_00636050
void __cdecl abortCoroutine(void* coroutine);                                    // FUN_00634830
void __cdecl resumeCoroutine(void* coroutine);                                   // FUN_00636260
void __cdecl yieldToScheduler();                                                 // FUN_00627360
void __cdecl handleFatalOverflow(void* schedulerThis);                           // FUN_00635a80

void CoroutineScheduler::executeCoroutine(void* coroutine, void* arg) {
    // Increment recursion depth
    uint16_t& depth = *(uint16_t*)((uint8_t*)coroutine + 0x2e);
    depth++;

    uint16_t currentDepth = depth;
    if (currentDepth > 199) {
        if (currentDepth == 200) {
            // Exact overflow limit reached: report and possibly trigger crash
            reportStackOverflow(coroutine, "C stack overflow");
        } else if (currentDepth > 224) {
            // Deeply nested: fatal error, call scheduler-specific handler
            handleFatalOverflow(this);
            return; // early exit after fatal error
        }
    }

    // Process the incoming event/message
    int result = processEvent(arg);
    if (result == 0) {
        // Event signaled failure: abort the coroutine
        abortCoroutine(coroutine);
    }

    // Resume the coroutine's main execution (its internal state machine)
    resumeCoroutine(coroutine);

    // Decrement recursion depth
    depth--;

    // Check if there is still work pending in the coroutine's associated state machine.
    // If no pending work, yield control to the scheduler to avoid busy-waiting.
    void* stateMachine = *(void**)((uint8_t*)coroutine + 0x10);
    uint32_t pendingCount = *(uint32_t*)((uint8_t*)stateMachine + 0x20);
    uint32_t processedCount = *(uint32_t*)((uint8_t*)stateMachine + 0x24);
    if (pendingCount <= processedCount) {
        yieldToScheduler();
    }
}