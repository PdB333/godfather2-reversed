// FUNC_NAME: Coroutine::execute
int Coroutine::execute()
{
    int *coroutineNode = *(int **)(this + 0x0c);
    // Validate coroutine node
    if (*(int **)(this + 0x08) <= coroutineNode || coroutineNode == nullptr 
        || *coroutineNode != 8 || coroutineNode[1] == 0) 
    {
        assertFailed(this, 1, "coroutine expected");
    }

    int state = coroutineResume(this); // Returns -1 for yield, else continuation ID
    int *stackPtr = *(int **)(this + 0x08);

    *stackPtr = 1; // opcode: push 1 (resume result)
    if (state >= 0) 
    {
        stackPtr[1] = 1; // flag: success
        *(int *)(this + 0x08) += 8; // advance stack
        coroutineCleanup();
        return state + 1;
    }

    stackPtr[1] = 0; // flag: yield
    *(int *)(this + 0x08) += 8; // advance stack
    stackPtr = *(int **)(this + 0x08);

    // Shift two-int values from below up by 2 slots (make room for frame)
    int *dst = stackPtr;
    int *src = stackPtr;
    while (stackPtr - 4 < src) 
    {
        src -= 2;
        dst[0] = src[0];
        dst[1] = src[1];
        dst -= 2;
    }
    // Copy the two ints from the new top-of-stack to the saved position
    int *newTop = *(int **)(this + 0x08);
    stackPtr[-4] = newTop[0];
    stackPtr[-3] = newTop[1];
    return 2; // yield state
}