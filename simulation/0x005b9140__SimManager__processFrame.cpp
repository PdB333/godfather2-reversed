// FUNC_NAME: SimManager::processFrame

undefined4 SimManager::processFrame(SimManager* thisPtr)
{
    uint* pAllocatedEvent;
    undefined4 unusedReturn;
    char tempChar;
    int entityCount;
    int* pComponentList;
    uint* pCurrentComponent;
    undefined4 someGlobal;
    int componentIndex;
    int iterCount;
    void** pCallbackEntry;
    int localIter;
    
    someGlobal = DAT_012055ac; // +0x12055ac: some global state
    SimManager* simMgr = SimManager::getInstance(); // 0x5a19c0
    pComponentList = *(int**)((int)simMgr + 0x18); // +0x18: pointer to array of component entries
    componentIndex = 0;
    if ((pComponentList != (int*)0x0) && (localIter = 0, 0 < *pComponentList)) {
        do {
            // Check if component has the 0x200 flag (maybe "needsUpdate")
            if ((*(uint*)(pComponentList[1] + componentIndex) & 0x200) != 0) {
                // Allocate event object (size 0x4c)
                pAllocatedEvent = (uint*)(*(code*)DAT_0119caf0)(0x4c, 0); // allocator
                if (pAllocatedEvent == (uint*)0x0) {
                    pAllocatedEvent = (uint*)0x0;
                }
                else {
                    // Initialize event structure
                    *pAllocatedEvent = *pAllocatedEvent & 0xffff8014 | 0x14;
                    *(undefined2*)((int)pAllocatedEvent + 2) = 0;
                    *pAllocatedEvent = *pAllocatedEvent | 0x8000;
                    uint* pEventData = pAllocatedEvent + 3;
                    *(undefined2*)(pAllocatedEvent + 1) = 2;
                    *(undefined2*)((int)pAllocatedEvent + 6) = 0;
                    pAllocatedEvent[2] = (uint)pEventData;
                    pEventData[0] = 0;
                    pEventData[1] = 0;
                    pAllocatedEvent[5] = 0;
                    pAllocatedEvent[6] = 0;
                }
                FUN_005b18b0(pAllocatedEvent); // likely Event::init or similar
                FUN_005a6e30(thisPtr); // maybe something like "applyEvent"
                int someGlobalCount = DAT_01221700; // another global counter
                if (0 < DAT_01221700) {
                    do {
                        unusedReturn = FUN_005a0d00(0); // get some object?
                        FUN_005a6e30(unusedReturn);
                        FUN_005a0c50(); // process something
                        someGlobalCount = someGlobalCount + -1;
                    } while (someGlobalCount != 0);
                }
                // Call method on component with parameters (param_1 interpreted as thisPtr)
                // Component entry is at pComponentList[1] + componentIndex + 8? Actually offset 8 from base
                FUN_005af370(*(undefined4*)(*(int*)(*(int*)((int)simMgr + 0x18) + 4) + 8 + componentIndex),
                             thisPtr, 0xffffffff);
                FUN_005a6f20(); // post-event cleanup
                FUN_005b19a0(); // maybe event destructor
            }
            pComponentList = *(int**)((int)simMgr + 0x18);
            localIter = localIter + 1;
            componentIndex = componentIndex + 0xc; // each component is 12 bytes
        } while (localIter < *pComponentList);
    }
    
    // Check loading/state conditions
    tempChar = FUN_005abd70(); // isGamePaused?
    if (tempChar == '\0') {
        tempChar = FUN_0059c5c0(0); // isSceneReady?
        if (tempChar != '\0') {
            FUN_0059c3b0(); // maybe resetLoadingState
            tempChar = FUN_005a4140(); // isTransitioning?
            if (tempChar == '\0') {
                FUN_0059c3b0();
                int mgr2 = FUN_005a3f20(); // get some other manager?
                int target = *(int*)(mgr2 + 0xc);
                goto LAB_005b92ea;
            }
        }
        target = 0;
    }
    else {
        target = (int)thisPtr + 4; // +4 offset for paused state?
    }
    
LAB_005b92ea:
    // Iterate over registered "onEnterFrame" callbacks
    pCallbackEntry = &PTR_s_onEnterFrame_0103ae34; // table of {flags, funcName, callback}
    do {
        // Check if the flag at pCallbackEntry[-1] has 0x200 set
        if ((((uint)pCallbackEntry[-1] & 0x200) != 0) && 
            (int callbackHandle = FUN_005bb050(target, *pCallbackEntry), callbackHandle != 0))
        {
            FUN_005a6890(thisPtr, callbackHandle, someGlobal);
        }
        pCallbackEntry = pCallbackEntry + 2; // each entry is 8 bytes? Actually +2 for pointer size
    } while ((int)pCallbackEntry < 0x103ae6c); // end of table
    
    return 1;
}