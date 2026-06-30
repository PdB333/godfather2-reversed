// FUNC_NAME: AudioTimer::setTimer
void __thiscall AudioTimer::setTimer(int thisPtr, undefined4 timerId, float delay) {
    int currentTimer;
    undefined4* timerData;
    
    // Cancel any existing timer
    currentTimer = *(int *)(thisPtr + 0x84);
    if (currentTimer != 0) {
        releaseTimer(currentTimer);
        timerData = *(undefined4 **)(currentTimer + 0x10);
        if (*(short *)(timerData + 1) != 0) {       // +0x04: ref count or active flag
            *(short *)((int)timerData + 6) = *(short *)((int)timerData + 6) - 1; // +0x06: decrement
            if (*(short *)((int)timerData + 6) == 0) {
                (**(code **)*timerData)(1);           // call destructor? argument 1
            }
        }
        finalizeTimerCleanup();
        *(int *)(thisPtr + 0x84) = 0;
    }
    
    // Allocate and initialize new timer
    TlsGetValue(DAT_01139810);                       // thread-local storage
    currentTimer = customAllocate(0x20, 0x27);        // 0x27 = allocation type
    delay = delay * DAT_00d5f040;                     // global time scale
    *(short *)(currentTimer + 4) = 0x20;              // store allocation size
    
    undefined3 handle1 = convertFloatToHandle(delay); // convert delay to internal format
    TlsGetValue(DAT_01139810);
    int unknownData = customAllocate(0x160, 0x31);    // 0x31 = allocation type
    *(short *)(unknownData + 4) = 0x160;
    undefined4 handle2 = createEventData(0xc, 0x17, 0);
    undefined3 newTimer = createTimerNode(handle1, &DAT_011397d0, handle2);
    *(int *)(thisPtr + 0x84) = newTimer;
    
    initTimer(newTimer);
    setupCallback(0x2000, timerId, 0);                // 0x2000 = callback flags
    return;
}