// FUNC_NAME: MissionManager::processMissionTransition
// Function address: 0x00655cb0
// Role: Handles state transitions for a mission based on conditions, allocating objectives and triggering updates.

void MissionManager::processMissionTransition(int missionObj) {
    char condFlag;
    int *missionMgr;
    int newObj;
    int *objPtr;
    uint handle[2];

    missionMgr = (int *)GetMissionManager();
    if ((missionMgr != (int *)0x0) && (missionMgr[0x6d] == 1)) { // offset 0x1b4: state field
        GetCurrentTime(0x40, handle); // maybe get game time or create timer
        condFlag = CheckMissionCondition();
        if (condFlag == '\0') {
            GetCurrentTime(0x20, handle);
            missionMgr[0x53] = handle[0]; // offset 0x14c: some handle
            GetCurrentTime(0x40, (int)missionMgr + 0x13b); // offset 0x13b: another slot
            GetCurrentTime(0x20, handle);
            missionMgr[0x51] = handle[0]; // offset 0x144
            if (handle[0] < 0x1b) { // 27
                condFlag = RandomBool(); // FUN_0046d790
                if (condFlag != '\0') {
                    condFlag = RandomBool();
                    if (condFlag == '\0') {
                        newObj = operatorNew(0x24);
                        if (newObj != 0) {
                            ConstructObjectiveTypeA(in_EAX); // FUN_00654840
                        }
                        ActivateObjective(); // FUN_00657990
                        if (*(char *)(missionMgr[0x54] + 0x20) == '\0') { // offset 0x150: object ptr
                            return;
                        }
                        condFlag = (**(code **)(*missionMgr[0x54] + 0x1c))(missionMgr[0x54], 1);
                        if (condFlag == '\0') {
                            return;
                        }
                    } else {
                        newObj = operatorNew(0x2c);
                        if (newObj != 0) {
                            ConstructObjectiveTypeB(in_EAX); // FUN_00654ad0
                        }
                        SetupObjectiveState(); // FUN_00657a10
                        int objPtr2 = missionMgr[0x56]; // offset 0x158: another object
                        if (*(char *)(objPtr2 + 0x24) == '\0') {
                            return;
                        }
                        condFlag = (**(code **)(*missionMgr[0x56] + 0x18))(objPtr2, 1);
                        if (condFlag == '\0') {
                            return;
                        }
                        handle[0] = *(uint *)(missionMgr[0x56] + 0x18);
                        if (handle[0] != 0) {
                            *(int *)(handle[0] + 8) = *(int *)(handle[0] + 8) + 1; // ref count?
                        }
                        ActivateObjective(); // FUN_00657960
                        UpdateUI(); // FUN_00652910
                    }
                    objPtr = missionMgr + 0x54; // pointer to object pointer
                    // Check if mission object matches current objective's owner
                    if ((*(int *)(missionObj + 0x30) == 0) ||
                        (*(int *)(*(int *)(missionObj + 0x30) + 0x10) != *(int *)(*objPtr + 0x10))) {
                        newObj = operatorNew(0x24);
                        if (newObj != 0) {
                            ConstructObjectiveTypeA(*(undefined4 *)(*objPtr + 0x10)); // FUN_0065e100
                        }
                        ActivateObjective(); // FUN_00657990
                    } else {
                        ActivateObjective(); // FUN_00657960
                    }
                    SetTargetPosition(missionMgr[0x55], handle, *objPtr); // FUN_0065e570
                    UpdatePresentation(); // FUN_006544b0
                    UpdateAudio(); // FUN_00652950
                    ClearMemory((int)missionMgr + 0x162, 0x10); // zero some buffer
                    *(char *)((int)missionMgr + 0x131) = 1; // set flag at offset 0x131
                }
                // Advance state
                missionMgr[0x6d] = 3; // state = 3
                missionMgr[0x67] = 0; // offset 0x19c: clear counter
                missionMgr[0x52] = 0; // offset 0x148: clear handle
                missionMgr[0x68] = *(int *)(missionObj + 100); // offset 0x1a0: store some value from mission
                AdvanceMissionState(missionObj); // FUN_00655ef0
            }
        }
    }
    return;
}