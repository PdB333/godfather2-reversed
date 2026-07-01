// FUNC_NAME: GodfatherGameManager::loadSaveGame
void __fastcall GodfatherGameManager::loadSaveGame(int thisPtr)
{
    uint *flagsPtr;
    char isComplete;
    int *managerPtr;
    undefined1 *stackFrame;
    undefined1 *retAddr;
    undefined4 arg0, arg1, arg2;
    undefined1 contextBuf[12];
    undefined1 *stackBuf;
    undefined4 stackSize;
    undefined4 someFlag;
    undefined1 fileBuf[128];

    // Clear bit 0x1000 (bit 12) and set bit 0x800 (bit 11) at +0x37C
    *(uint *)(thisPtr + 0x37C) = *(uint *)(thisPtr + 0x37C) & 0xFFFFEFFF;
    *(uint *)(thisPtr + 0x37C) = *(uint *)(thisPtr + 0x37C) | 0x800;

    // Get singleton manager (e.g., SimManager or GodfatherGameManager)
    managerPtr = (int *)GodfatherGameManager::getInstance();
    managerPtr = (int *)(**(code **)(*managerPtr + 4))(); // virtual call to get a subsystem

    if (managerPtr != (int *)0x0) {
        // Push async context
        pushAsyncContext();
        stackSize = 0x80;
        allocateStackBuffer();  // sets up stackBuf
        stackBuf = fileBuf;
        someFlag = 1;
        // Virtual call to subsystem to get file path/name into contextBuf
        (**(code **)(*managerPtr + 0x2C))(contextBuf);
        isComplete = checkAsyncComplete();
        if (isComplete == '\0') {
            // Reset global load state
            gLoadState1 = 0;
            gLoadState2 = 0;
            gLoadState3 = 0;
            gLoadState4 = 0;
            gLoadState5 = 0;
            gLoadState6 = 0;
            // Set loading flag on global game manager
            if (*(int *)(gGameManager + 0x40) != 0) {
                flagsPtr = (uint *)(*(int *)(gGameManager + 0x40) + 0x7C);
                *flagsPtr = *flagsPtr | 0x800;
            }
            arg2 = 1000;
            arg1 = 0;
            arg0 = 0;
            retAddr = &loadGameCallback;  // LAB_008a4920
            stackFrame = &stackArea;      // stack0xffffff3c
            // Start async operation (passing stack frame for coroutine)
            (**(code **)*managerPtr)(stackFrame, thisPtr, &loadGameCallback, 0, 0, 1000);
            continueLoadGame(stackFrame, thisPtr, retAddr, arg0, arg1, arg2);
        }
        popAsyncContext();
    }
    return;
}