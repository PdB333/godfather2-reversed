// FUNC_NAME: conditionalCall
// Function address: 0x004b1e60
// Role: Conditional wrapper - if a global flag (0x01218014) is non-zero, calls a secondary function (0x0064d980).
// Used as a common check in multiple update paths, likely for one-time initialization or deferred execution.

void conditionalCall(void)
{
    if (g_bActionFlag) // Global flag at 0x01218014, possibly indicating a pending action
    {
        performDeferredAction(); // Function at 0x0064d980, executes the deferred task
    }

    return;
}