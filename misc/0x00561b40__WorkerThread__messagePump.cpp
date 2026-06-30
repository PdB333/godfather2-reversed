// FUNC_NAME: WorkerThread::messagePump

int WorkerThread::messagePump(void) {
    char exitFlag;
    int uVar2;
    void* pvVar3;
    int* puVar4;
    int uStack_344;
    void* local_340[207];

    // Initialize thread with manager and work queue
    FUN_00aa23a0(gThreadManager, *(int*)(*(int*)((int)this->managerPtr + 0x130)));
    // Setup stack buffer (likely for message queue or temporary data)
    FUN_00c6e980(local_340);
    uVar2 = this->vtableOrId;
    TlsGetValue(gThreadLocalIndex);
    uVar2 = FUN_00aa28b0(uVar2, 1);
    FUN_00aa2360(uVar2, this->vtableOrId);
    // If there is work count, consume from thread local
    if (0 < this->workCount) {
        pvVar3 = TlsGetValue(gThreadLocalDataIndex);
        FUN_00aa43c0(pvVar3, this->workCount);
    }
    FUN_00aad110(); // enter critical section?
    exitFlag = this->exitFlag;
    while (exitFlag == '\0') {
        pvVar3 = TlsGetValue(gThreadLocalDataIndex);
        FUN_00aa42f0(pvVar3); // wait for message/event
        uStack_344 = FUN_009e5d50(); // get next message
        FUN_009e5d40(&uStack_344); // dispatch message
        if (0 < this->workCount) {
            puVar4 = (int*)TlsGetValue(gThreadLocalDataIndex);
            this->workResult1 = *puVar4;
            pvVar3 = TlsGetValue(gThreadLocalDataIndex);
            this->workResult2 = *(int*)((int)pvVar3 + 4);
        }
        FUN_00aad120(1); // leave critical section?
        FUN_00aad110(); // re-enter critical section?
        exitFlag = this->exitFlag;
    }
    FUN_00aa2360(0, 0);
    TlsGetValue(gThreadLocalIndex);
    FUN_00aa28e0(uVar2);
    FUN_00c6e9b0();
    FUN_00aad120(1);
    local_340[0] = &gSomeVtable;
    FUN_00aa2650(); // final cleanup
    return 0;
}