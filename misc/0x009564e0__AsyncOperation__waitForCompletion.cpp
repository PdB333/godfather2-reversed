// FUNC_NAME: AsyncOperation::waitForCompletion
void __thiscall AsyncOperation::waitForCompletion(uint param_2) {
    char isReady;
    int status;
    int result;

    // Begin the async operation with a hash identifier (likely a resource ID or operation type)
    beginAsyncOperation(param_2, 0xb3ea5752);

    isReady = isAsyncOperationReady();
    while (isReady == '\0') {
        // Process pending operations or yield
        processAsyncQueue();

        // Check if there is a result available
        result = checkAsyncResult();
        if (result == 0) {
            // If no error, get the next completed operation
            result = processAsyncQueue(); // note: reuse of processAsyncQueue, may be a different function
            // Store the result data (at offset +8 of the returned object) into this+0x54
            *(int *)(this + 0x54) = *(int *)(result + 8);
        }

        // Yield to other tasks
        yieldProcessing();

        isReady = isAsyncOperationReady();
    }

    // End the async operation, cleanup
    endAsyncOperation(param_2);
}