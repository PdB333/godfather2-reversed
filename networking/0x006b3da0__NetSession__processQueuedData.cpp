// FUNC_NAME: NetSession::processQueuedData
void __thiscall NetSession::processQueuedData() {
    int wishCount; // local_c, but actually from offset
    int list2Count;
    int list1Count;
    bool bProcessedList1 = false;

    // Process first list (e.g., incoming packets) at +0x9c (array) and +0xa0 (count)
    list1Count = *(int *)(this + 0xa0);
    while (list1Count = list1Count - 1, list1Count >= 0) {
        uint element = *(uint *)(*(int *)(this + 0x9c) + list1Count * 4);
        int threadId = getCurrentThreadId(); // FUN_007914e0
        if (threadId != *(int *)(this + 0x40)) {
            enterCriticalSection(); // FUN_007915b0
            processIncomingPacket(element, this, 1); // FUN_008c3a10
            bProcessedList1 = true;
        }
    }

    // Process second list (e.g., outgoing/ack packets) at +0x84 (array) and +0x88 (count)
    list2Count = *(int *)(this + 0x88) - 1;
    if (list2Count >= 0) {
        do {
            uint element = *(uint *)(*(int *)(this + 0x84) + list2Count * 4);
            enterCriticalSection(); // FUN_007915b0
            processOutgoingPacket(element, this); // FUN_008c2e50
            list2Count = list2Count - 1;
        } while (list2Count >= 0);
    }
    else if (!bProcessedList1) {
        // No items processed in either list, skip further check?
        // Fall through to scope guard
    }

    // RAII-style scope guard to lock global queue mutex
    struct QueueScopeGuard {
        int **vtbl;
        int globalVar;
        char flag;
        int *thisPtr;
    };
    QueueScopeGuard guard;
    guard.vtbl = (int **)&PTR_LAB_00d5dbb0; // vtable for scope guard?
    guard.globalVar = DAT_0112a5a4; // some global int
    guard.flag = 0;
    guard.thisPtr = this;
    initializeScopeGuard(&guard, 0); // FUN_00408a00

    // If all queues are empty, unlock and return
    if ( *(int *)(this + 0x88) == 0 &&
         *(int *)(this + 0xa0) == 0 &&
         *(int *)(this + 0xac) == 0 &&
         *(int *)(this + 0xb8) == 0 ) {
        unlockGlobalQueue(&DAT_0112a640); // FUN_004086d0
        return;
    }
    lockGlobalQueue(&DAT_0112a640); // FUN_00408680
    return;
}