// FUNC_NAME: NetSession::dispatchIncomingMessage
// Function at 0x00633bc0:
// Core dispatch for incoming network messages. Checks initialization flag in session state,
// initializes if needed, then routes based on message type (type 6 handled specially).

void* __thiscall NetSession::dispatchIncomingMessage(int thisPtr, int param_2, undefined4 param_3, undefined4 param_4) {
    int* pMessageType; // pointer to message type field
    void* pState;      // state pointer from FUN_00637f90
    byte* pInitFlag;   // flag at offset 6 in upper 32 bits of state
    undefined8 state64; // 64-bit return from initializer

    // Check if the session's "initialized" flag is set (bit 0 at nested offset)
    // Layout: param_2+4 -> some object, +8 -> another object, +6 -> byte
    if ((*(byte*)(*(int*)(*(int*)(param_2 + 4) + 8) + 6) & 1) == 0) {
        state64 = getNetState(); // FUN_00637f90 - returns 64-bit value
        pMessageType = (int*)(int)state64; // lower 32 bits as pointer
        if (*pMessageType != 0) {
            goto after_init;
        }
        pInitFlag = (byte*)((int)(state64 >> 32) + 6); // upper 32 bits + offset 6
        *pInitFlag = *pInitFlag | 1; // set initialization flag
    }
    pMessageType = (int*)0x0; // reset if not initialized
after_init:
    if (pMessageType == (int*)0x0) {
        return (void*)&DAT_00e2a93c; // sentinel/null return
    }
    if (*pMessageType == 6) {
        handleMessageType6(thisPtr, pMessageType, param_2, param_3); // FUN_00633ac0
        return *(void**)(thisPtr + 8); // return pointer at offset 8 from this
    }
    // All other types delegate to generic handler
    return (void*)handleGenericMessage(thisPtr, pMessageType, param_3, param_4); // FUN_00633cb0
}