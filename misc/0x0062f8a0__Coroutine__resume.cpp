// FUNC_NAME: Coroutine::resume
undefined4 Coroutine::resume(void) {
    int* stackPtr;          // piVar1
    undefined4* strResult;  // puVar2
    int* coroutine;         // iVar3
    undefined4 string;      // uVar4

    // Get stack top pointer at +0x0c
    stackPtr = *(int**)(this + 0x0c);
    // Validate: stack base (+0x08) must be <= stack top, top not null, and top word must be marker 8
    if ((((*(int**)(this + 0x08) <= stackPtr) || (stackPtr == (int*)0x00)) || (*stackPtr != 8)) ||
        (coroutine = stackPtr[1], coroutine == (int*)0x00)) {
        coroutine = (int*)errorExpected("coroutine expected"); // 0x00627a20
    }

    if ((int)this == (int)coroutine) {
        // We are resuming the currently running coroutine -> yield
        // Check if yield is allowed: scheduler at this+0x10, counters at +0x20 and +0x24
        if (*(uint32*)(*(int32*)(this + 0x10) + 0x20) <= *(uint32*)(*(int32*)(this + 0x10) + 0x24)) {
            yield(); // 0x00627360
        }
        // Set new state: stack base now holds marker (4 = running)
        strResult = *(undefined4**)(this + 0x08);
        *strResult = 4;
        string = pushString("running", 7); // 0x00638920
        strResult[1] = string;
        // Advance stack base by 8 bytes (two ints)
        *(int32*)(this + 0x08) = *(int32*)(this + 0x08) + 8;
        return 1;
    }

    // Resume a different coroutine: check if it has finished
    if ((*(int32*)((int)coroutine + 0x14) == *(int32*)((int)coroutine + 0x28)) &&
        ((*(int32*)((int)coroutine + 0x08) - *(int32*)((int)coroutine + 0x0c) & 0xfffffff8U) == 0)) {
        // Coroutine is done -> push "dead" (or "normal") constant string
        pushString("completed", 4); // 0x00625c60, DAT_00e41d10 assumed to be "completed"
        return 1;
    }
    // Otherwise still suspended
    pushString("suspended", 9); // 0x00625c60
    return 1;
}