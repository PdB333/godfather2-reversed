// FUNC_NAME: LuaState::handleTailCall
void __thiscall LuaState::handleTailCall(void)
{
    int *callInfoRead;  // +0xc: read pointer for call info
    int *callInfoWrite; // +0x8: write pointer for call info
    float tailCallThreshold = DAT_00e2b1a4; // global threshold for tail call optimization

    callInfoRead = *(int **)(this + 0xc);
    callInfoWrite = *(int **)(this + 0x8);

    // Fast path: if there's a call info to read and its type is 6 (C function?), copy it directly
    if (callInfoRead < callInfoWrite) {
        if ((callInfoRead != NULL) && (*callInfoRead == 6)) {
            *callInfoWrite = *callInfoRead;
            callInfoWrite[1] = callInfoRead[1];
            *(int **)(this + 0x8) = callInfoWrite + 2; // advance write pointer by 2 ints (8 bytes)
            return;
        }
        // If the call info is present and has a positive type, evaluate a condition
        if ((callInfoRead < callInfoWrite) && (callInfoRead != NULL) && (0 < *callInfoRead)) {
            tailCallThreshold = FUN_00628080(); // returns a float (e.g., based on stack depth)
        }
    }

    // If threshold is negative, trigger error handling
    if ((int)tailCallThreshold < 0) {
        FUN_00627a20(); // error/longjmp
    }

    // Check if tail call is allowed (maybe recursion depth check)
    if (FUN_00632b70() == 0) {
        FUN_00627a20(); // error/longjmp
    }

    FUN_00632fb0(); // perform the tail call reclamation

    // Now examine the call info just before the write pointer (the current call we are about to pop?)
    callInfoRead = (int *)(*(int **)(this + 0x8) - 2);
    // If that call info is present and has type 0, that's invalid for tail call
    if ((callInfoRead != NULL) && (*callInfoRead == 0)) {
        FUN_00627bd0("no function environment for tail call at level %d", (int)tailCallThreshold);
        // Trigger a debug break
        ((code (*)(void))SWI(3))(); // software interrupt 3
        return;
    }
}