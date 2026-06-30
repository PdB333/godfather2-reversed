// FUNC_NAME: Coroutine::step
undefined4 Coroutine::step(int this) // __thiscall
{
    int *stackBottom;
    int *stackPtr;
    int resumePtr;
    undefined4 *stackFrame;
    undefined4 token;
    int *nextCoroutine;

    // +0x0c: pointer to bottom of stack frame (first element)
    stackBottom = *(int **)(this + 0xc);
    // +0x08: current stack top pointer
    stackPtr = *(int **)(this + 0x8);

    // Validate that the current stack frame is a valid coroutine frame
    // The stack frame must: exist, be non-null, have first dword == 8 (coroutine marker),
    // and second dword (pointer to the owning coroutine) must be non-null.
    if ((stackPtr <= stackBottom) || (stackBottom == (int *)0x0) ||
        (*stackBottom != 8) || (stackBottom[1] == 0))
    {
        // Error: stack does not contain a coroutine frame
        FUN_00627a20(this, 1, "coroutine expected");
    }

    // The owning coroutine of the current stack frame
    resumePtr = stackBottom[1];

    if (this == resumePtr)
    {
        // We are the coroutine at the top of the stack: push a "running" token
        // +0x10: pointer to a context (e.g., CoroutineScheduler) with capacity at +0x20 and used at +0x24
        int *context = *(int **)(this + 0x10);
        if (*(uint *)(context + 0x20) <= *(uint *)(context + 0x24))
        {
            // Context slot full? Yield/reschedule
            FUN_00627360();
        }

        // Write the token (opcode 4 = "running") and string identifier
        stackFrame = *(undefined4 **)(this + 0x8);
        *stackFrame = 4;
        token = FUN_00638920(this, "running", 7);
        stackFrame[1] = token;
        // Advance stack pointer by 8 bytes
        *(int *)(this + 0x8) = *(int *)(this + 0x8) + 8;
        return 1;
    }
    else
    {
        // We are waiting for another coroutine (resumePtr) to complete
        nextCoroutine = (int *)resumePtr;
        // Check if that coroutine has finished:
        // +0x14 and +0x28: some state markers (e.g., stack empty flag and something else)
        // Also check if its stack pointer is at base (stackPtr - stackBottom == 0 mod 8)
        if ((nextCoroutine[0x14] == nextCoroutine[0x28]) &&
            (((nextCoroutine[2] - nextCoroutine[3]) & 0xfffffff8U) == 0))
        {
            // The other coroutine is done: print "done" (from global DAT_00e41d10, 4 chars)
            FUN_00625c60(&DAT_00e41d10, 4);
            return 1;
        }
        // Otherwise still suspended: print "suspended" (9 chars)
        FUN_00625c60("suspended", 9);
        return 1;
    }
}