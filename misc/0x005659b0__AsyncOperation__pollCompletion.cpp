// FUNC_NAME: AsyncOperation::pollCompletion
int __thiscall AsyncOperation::pollCompletion(void* this, int operationID, bool& outDone) {
    int state;
    char buffer[128]; // buffer for operation state data

    // Called to check the state of an asynchronous operation
    // +0x20: pointer to an internal state machine or operation manager
    state = FUN_00569bf0(*(int*)((int)this + 0x20), operationID, buffer);
    if (state == 0) {
        // Operation not started or invalid
        return 0;
    }
    if (state == 2) {
        // Operation completed; process result
        FUN_005655c0(buffer, (int)&outDone);
        if (outDone == false) {
            return 0;
        }
    } else if (state == 3) {
        // Operation failed
        return 0;
    }
    return 1; // Operation still pending or successful completion
}