// FUNC_NAME: Coroutine::resume
int __thiscall Coroutine::resume(int thisPtr, int arg)
{
    int success;
    int resultCount;

    success = coRoutineCheckStack();
    if (success == 0) {
        coRoutineError("too many arguments to resume");
    }
    coRoutinePush(arg);
    success = coRoutineCheckCondition();
    if (success == 0) {
        // +0x8: pointer to result list start?
        // +0xC: pointer to result list end?
        int start = *(int *)(thisPtr + 8);
        int end = *(int *)(thisPtr + 0xC);
        success = coRoutineCheckStack();
        if (success == 0) {
            coRoutineError("too many results to resume");
        }
        coRoutinePush(thisPtr);
        return (start - end) >> 3; // number of results (each maybe 8 bytes)
    }
    coRoutinePush(thisPtr);
    return -1;
}