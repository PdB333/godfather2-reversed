// FUNC_NAME: AsyncOperation::updateStatus
uint __fastcall AsyncOperation::updateStatus(int this) {
    uint status;
    uint result;
    int resultBuffer[2] = {0, 0};

    // Start the asynchronous operation with callback function and arguments from object state
    status = startOperation(0, *(int *)(this + 0x14c), *(int *)(this + 0x150),
                            s_completionCallback, this);

    result = status;
    // If callback has been invoked (set resultBuffer[0] != 0), process the result
    if (resultBuffer[0] != 0) {
        result = processResult(resultBuffer);
    }

    // Operation completed with status 2 -> return error code from secondary function
    if (status == 2) {
        result = getErrorCode();               // FUN_006feb30
        return result & 0xffffff00;
    }

    // Operation completed with status 1 -> set flag at offset 0x140 (ongoing?)
    if (status == 1) {
        *(char *)(this + 0x140) = 1;
    }

    // Return final status with lower byte cleared (status flags masked out)
    return result & 0xffffff00;
}