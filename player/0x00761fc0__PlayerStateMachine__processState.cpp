// FUNC_NAME: PlayerStateMachine::processState
void __fastcall PlayerStateMachine::processState(int thisPtr)
{
    int* ptr_0x54;
    int* ptr_0x60;
    int object_0x70_0x14;
    int playerPtr;
    uint someValue;
    uint flags;
    char debugBuffer1[4];   // local_5c
    char debugBuffer2[28];  // local_58
    char debugBuffer3[4];   // local_3c
    char debugBuffer4[12];  // local_38
    char debugBuffer5[44];  // local_2c
    int* cleanupList;       // local_7c
    int localArray[7];      // local_78

    // +0x80: bit 4 (0x10) clear
    *(uint*)(thisPtr + 0x80) &= 0xFFFFFFEF;

    ptr_0x54 = (int*)(thisPtr + 0x54);
    if (*ptr_0x54 != 0) {
        operatorDelete(ptr_0x54);   // FUN_004daf90
        *ptr_0x54 = 0;
    }
    // +0x5c likely size or counter
    *(int*)(thisPtr + 0x5c) = 0;

    ptr_0x60 = (int*)(thisPtr + 0x60);
    if (*ptr_0x60 != 0) {
        operatorDelete(ptr_0x60);
        *ptr_0x60 = 0;
    }
    // +0x68: similar counter
    *(int*)(thisPtr + 0x68) = 0;

    // +0x70: pointer to another object; deref +0x14 to get target
    object_0x70_0x14 = *(int*)(*(int*)(thisPtr + 0x70) + 0x14);
    playerPtr = *(int*)(thisPtr + 0x50);
    someValue = *(uint*)(playerPtr + 0x5C4); // from player at large offset

    if (object_0x70_0x14 != 0 && (*(byte*)(object_0x70_0x14 + 0x4E) & 0x0A) != 0) {
        // Begin state transition
        FUN_00760190(playerPtr, 10, someValue, playerPtr + 0x2194, 1, 0x3F800000);
        int debugMgr = getDebugManager(); // FUN_00471610
        debugLog(debugMgr + 0x30, debugBuffer3, debugString_00d92d0c); // "state start"
        destroyArray(debugBuffer4); // FUN_005f7ba0
        destroyArray(debugBuffer5);

        if (*ptr_0x54 != 0 && *(int*)(thisPtr + 0x5C) != 0) {
            // Already in transition, set flag and finish
            *(uint*)(thisPtr + 0x80) |= 0x10;
            finishProcessing(); // FUN_00760210
            return;
        }

        // Continue transition
        FUN_00761ab0(playerPtr, 10, someValue, playerPtr + 0x2194);
        debugMgr = getDebugManager();
        debugLog(debugMgr + 0x30, &cleanupList, debugString_00d92d08); // "state continue"
        destroyArray(localArray);

        if (*ptr_0x54 == 0 || *(int*)(thisPtr + 0x5C) == 0) {
            FUN_007600d0(10, someValue, playerPtr + 0x2194, 0);
            debugMgr = getDebugManager();
            debugLog(debugMgr + 0x30, debugBuffer1, debugString_00d92d04); // "state finish"
            destroyArray(debugBuffer2);
            resetState(); // FUN_00760130
        }

        if (*ptr_0x54 == 0 || *(int*)(thisPtr + 0x5C) == 0) {
            uint index = globalCounter & globalFlagMask; // DAT_010c2678 & DAT_012054b4
            globalFlagMask++; // DAT_012054b4
            // Call some update with computed animation data
            FUN_005f5c60(object_0x70_0x14,
                         *(int*)(object_0x70_0x14 + 0x20) +
                         (int)((float)*(ushort*)(object_0x70_0x14 + 0xC) *
                               *(float*)(&animationTable + index * 4)) * 0x24);
        }

        cleanupList = &functionTable_00d654d0; // PTR_FUN_00d654d0
        if (localArray[0] != 0) {
            operatorDelete(localArray);
        }
        finishProcessing(); // FUN_00760210
    }
}