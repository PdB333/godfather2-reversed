// FUNC_NAME: globalProcessFunction
// Address: 0x00633920
// Role: Fetches a process object, performs an operation on it, then finalizes.
void globalProcessFunction(void)
{
    undefined4 processHandle; // Handle from getProcessObject
    processHandle = getProcessObject(&processHandle); // Get object/output via stack pointer
    processObject(processHandle); // Operate on the handle
    finalizeProcess(); // Cleanup/commit
    return;
}