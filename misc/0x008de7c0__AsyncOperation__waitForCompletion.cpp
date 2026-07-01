// FUNC_NAME: AsyncOperation::waitForCompletion

void __thiscall AsyncOperation::waitForCompletion(AsyncOperation* thisPtr, void* operationHandle)
{
    char isFinished;
    void* resultPtr;

    // Begin the async operation (e.g., start streaming)
    startOperation(operationHandle);
    // Set a timeout (0xfd678400 might be a large timeout value in microseconds or engine ticks)
    setTimeout(operationHandle, 0xfd678400);

    isFinished = isOperationFinished();
    while (isFinished == '\0') {
        // Process messages/yield to avoid busy-wait
        processMessages();
        // Check if operation has finished
        if (isOperationFinished() == 0) {
            // Operation finished: retrieve result
            resultPtr = getResultPointer();
            thisPtr->resultField = *(int*)((char*)resultPtr + 8); // +0x270 offset in thisPtr, store value at offset 8
        }
        // Yield or sleep to let other tasks run
        yield();
        isFinished = isOperationFinished();
    }
}