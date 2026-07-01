// FUNC_NAME: NetSession::processEvent

void __thiscall NetSession::processEvent(int thisPtr, undefined4 arg0, undefined4 arg1, undefined4 arg2) {
    bool enableDebug = (arg2 != 0);
    int eventType = *(int *)(thisPtr + 4);  // +0x04: event type/subtype
    void* sendHandler = *(void **)(thisPtr + 8);  // +0x08: sender handler (e.g., outbound)
    void* recvHandler = *(void **)(thisPtr + 0xc); // +0x0c: receiver handler (e.g., inbound)

    if (eventType == 0xb) {
        pushDebugScope(&g_scopeOuter);  // DAT_00e36d30
        if (enableDebug) {
            ++g_suspendCount;          // DAT_0112af24
            suspendDebug();            // FUN_0077a9a0
        }
        pushDebugScope(g_scopeByType + (eventType * 2));  // PTR_DAT_00e51cdc indexed by type
        if (sendHandler != NULL) {
            callVirtualMethod(sendHandler, 0x10, arg0, arg1, arg2);
        }
    }
    else {
        pushDebugScope(&g_scopeOuter);
        if (enableDebug) {
            ++g_suspendCount;
            suspendDebug();
        }
        if (sendHandler != NULL) {
            callVirtualMethod(sendHandler, 0x10, arg0, arg1, arg2);
        }
        pushDebugScope(&g_scopeInner);  // DAT_00e337ec
        if (enableDebug) {
            suspendDebug();
        }
        pushDebugScope(g_scopeByType + (eventType * 2));
        pushDebugScope(&g_scopeInner);
        if (enableDebug) {
            suspendDebug();
        }
        if (recvHandler != NULL) {
            callVirtualMethod(recvHandler, 0x10, arg0, arg1, arg2);
        }
    }
    if (enableDebug) {
        --g_suspendCount;
        suspendDebug();
    }
    pushDebugScope(&g_scopeExit);  // DAT_00e36d34
}