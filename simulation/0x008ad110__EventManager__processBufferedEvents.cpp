// FUNC_NAME: EventManager::processBufferedEvents
void __thiscall EventManager::processBufferedEvents(int this, void* buffer, int* outParam3, int* outParam4, int* outParam5, int* outParam6, int* outParam7, int* outParam8, int* outParam9)
{
    char hasNext;
    int iVar2;
    uint uVar3;
    bool flag_local;
    undefined** iteratorVtable;
    int iteratorState;
    int containerPtr;
    uint data0;
    uint data1;
    uint data2;
    undefined** cleanupVtable;
    int stackData[8]; // size 8 ints

    iVar2 = Game::isInitialized(); // FUN_00481610
    if (((iVar2 != 0) && (Game::isRunning(), g_pNetworkManager != 0)) &&
        (containerPtr = *(int*)(this + 0x60), containerPtr != 0)) {
        iteratorVtable = &PTR_FUN_00e35c30; // iterator vtable
        flag_local = 0;
        data0 = 0;
        data1 = 0;
        data2 = 0;
        iteratorState = 0;
        if (*(int*)(containerPtr + 0x14) == 0) {
            containerPtr = 0;
        }
        FUN_004bb740(&cleanupVtable); // Some initializer/sentinel
        hasNext = FUN_008a7380(&cleanupVtable); // Check if iterator has next
        iVar2 = 32;
        if (hasNext != 0) {
            while (true) {
                if ((iteratorState == 0) && (containerPtr == 0)) goto LAB_008ad214;
                (*(code*)*iteratorVtable)(); // Get current element
                hasNext = FUN_008a7380(buffer); // Check buffer validity?
                iVar2 = 32;
                if (hasNext == 0) break;
                (*(code*)iteratorVtable[1])(); // Move to next
            }
        }
        while (true) {
            if ((iteratorState == 0) && (containerPtr == 0)) goto LAB_008ad214;
            if (iVar2 == 0) break;
            uVar3 = (*(code*)*iteratorVtable)(); // Get current element
            FUN_004bc440(uVar3); // Process element (deserialize?)
            (*(code*)iteratorVtable[1])(); // Move to next
            iVar2 = iVar2 - 1;
        }
        if ((iteratorState == 0) && (containerPtr == 0)) {
LAB_008ad214:
            *outParam3 = stackData[1];
            *outParam4 = stackData[2];
            *outParam5 = stackData[3];
            *outParam6 = stackData[4];
            flag_local = 1;
            *outParam7 = stackData[5];
            *outParam8 = stackData[6];
            *outParam9 = stackData[7];
        } else {
            iVar2 = (*(code*)*iteratorVtable)(); // Get current element
            *outParam3 = *(int*)(iVar2 + 4);
            *outParam4 = *(int*)(iVar2 + 8);
            *outParam5 = *(int*)(iVar2 + 0xc);
            *outParam6 = *(int*)(iVar2 + 0x10);
            *outParam7 = *(int*)(iVar2 + 0x14);
            *outParam8 = *(int*)(iVar2 + 0x18);
            *outParam9 = *(int*)(iVar2 + 0x1c);
        }
        iVar2 = FUN_009c8e50(0x68); // allocate 104 bytes
        if (iVar2 == 0) {
            uVar3 = 0;
        } else {
            uVar3 = FUN_008aba80(this); // Construct Event object
        }
        FUN_008ab240(buffer, &flag_local, &data0); // Initialize event from buffer
        FUN_0064ef60(uVar3); // Add event to queue
        cleanupVtable = &PTR_LAB_00e35c24; // cleanup vtable
        FUN_004bc3f0(); // release iterator resources
    }
    return;
}