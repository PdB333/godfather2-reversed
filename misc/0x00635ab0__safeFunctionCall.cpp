// FUNC_NAME: safeFunctionCall
// Function address: 0x00635ab0
// Role: Wrapper that executes a callback with exception handling using setjmp/longjmp.
// The object at param_1 has a saved jump buffer pointer at +0x50 that is temporarily
// replaced with a local buffer to catch crashes/exceptions during the callback.

int safeFunctionCall(void* thisPtr, void (*callback)(void*, int), int param)
{
    int savedJumpBufferPtr;   // saved value from offset +0x50
    jmp_buf localJmpBuf;      // local jump buffer for setjmp

    savedJumpBufferPtr = *(int*)((char*)thisPtr + 0x50);
    *(int*)((char*)thisPtr + 0x50) = (int)&localJmpBuf;

    int result = 0;
    int setjmpResult = __setjmp3(localJmpBuf, 0);
    if (setjmpResult == 0) {
        // Normal execution: call the callback
        callback(thisPtr, param);
        // Restore the saved jump buffer pointer
        *(int*)((char*)thisPtr + 0x50) = savedJumpBufferPtr;
        return result;
    }
    else {
        // Longjmp occurred (exception): restore pointer and return 0
        *(int*)((char*)thisPtr + 0x50) = savedJumpBufferPtr;
        return result;
    }
}