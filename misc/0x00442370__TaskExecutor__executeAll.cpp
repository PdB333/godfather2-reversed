// FUNC_NAME: TaskExecutor::executeAll
void TaskExecutor::executeAll()
{
    int i = 0;
    if (0 < *(int *)(this + 0x28)) {  // +0x28: repeatCount (number of times to call the per‑tick function)
        do {
            FUN_00441d30();  // called each tick – likely processes a single task or updates state
            i = i + 1;
        } while (i < *(int *)(this + 0x28));
    }
    return;
}