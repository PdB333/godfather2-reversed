// FUNC_NAME: MissionManager::update
void __fastcall MissionManager::update(void *thisPtr) {
    int *gameManagerPtr = *(int **)((int)thisPtr + 0x58);            // +0x58: pointer to GameManager
    int *activeMissionsHead = (int *)((int)thisPtr + 0x78);          // +0x78: head of active mission list (intrusive list)
    DAT_0112a868 = 1;                                                // Global flag: mission system active

    if (*activeMissionsHead != 0 && *activeMissionsHead != 0x48) 
        goto LAB_007da2b2;                                           // Skip if list is already populated with a valid node

    if (DAT_0112a874 == 0) {
        int newNodeMem = FUN_0043b910(0x60, 0);                      // Allocate 0x60 bytes (size of mission node?)
        if (newNodeMem != 0) {
            FUN_006d1310();                                          // Initialize node?
        }
        *(unsigned int *)((int)thisPtr + 0xc4) |= 1;                 // +0xC4: flag bitfield, set bit 0
        if (DAT_0112a874 != 0) 
            goto LAB_007da238;
        newNodePtr = 0;
    } else {
LAB_007da238:
        newNodePtr = DAT_0112a874 + 0x48;                            // Offset of node structure?
    }

    if (*activeMissionsHead != newNodePtr) {
        if (*activeMissionsHead != 0) {
            FUN_004daf90(activeMissionsHead);                        // Unlink current head
        }
        *activeMissionsHead = newNodePtr;
        if (newNodePtr != 0) {
            *(int *)((int)thisPtr + 0x7c) = *(int *)(newNodePtr + 4); // +0x7c: store back pointer?
            *(int **)(newNodePtr + 4) = activeMissionsHead;           // Link node back to list head
        }
    }

    int *nodeBase;
    if (*activeMissionsHead == 0) {
        nodeBase = 0;
    } else {
        nodeBase = (int *)(*activeMissionsHead - 0x48);             // Adjust to start of mission node
    }

    (**(code **)(*nodeBase + 0x24))(*(undefined4 *)(&DAT_00002494 + *(int *)((int)thisPtr + 0x58))); // Call vtable method (offset 0x24) with some context

    int *nodeBase2;
    if (*activeMissionsHead == 0) {
        nodeBase2 = 0;
    } else {
        nodeBase2 = (int *)(*activeMissionsHead - 0x48);
    }
    int context = *(int *)(&DAT_00002494 + *(int *)((int)thisPtr + 0x58)); // Context from table at 0x2494
    float duration = (float)FUN_006d03a0(3, 0);                     // Get random duration?
    FUN_00424dc0(context, nodeBase2, duration, 3, 0);               // Schedule something (e.g., timer)

LAB_007da2b2:
    int *pendingMissionsHead = (int *)((int)thisPtr + 0x80);        // +0x80: head of pending mission list
    if (*(int *)((int)thisPtr + 0x80) == 0) {
        int a = *(int *)(gameManagerPtr + 0x2c54);                  // GameManager fields for mission spawn conditions
        int b = *(int *)(gameManagerPtr + 0x2c58);
        int c = *(int *)(gameManagerPtr + 0x2c5c);
        int d = *(int *)(gameManagerPtr + 0x2c60);
        if (a == 0 && b == 0 && c == 0 && d == 0) {
            // No pending mission data: create generic mission
            undefined4 *pool = (undefined4 *)FUN_009c8f80();         // Get memory pool
            int newMission = 0;
            undefined4 allocParams[3] = {2, 0x10, 0};              // Pool allocation parameters
            int mem = (**(code **)*pool)(0x1c0, &allocParams);     // Allocate 0x1c0 bytes for mission object
            if (mem != 0) {
                newMission = FUN_006dae60();                        // Construct generic mission?
            }
            if (*pendingMissionsHead != newMission) {
                if (*pendingMissionsHead != 0) {
                    FUN_004daf90(pendingMissionsHead);
                }
                *pendingMissionsHead = newMission;
                if (newMission != 0) {
                    *(int *)((int)thisPtr + 0x84) = *(int *)(newMission + 4);
                    *(int **)(newMission + 4) = pendingMissionsHead;
                }
            }
        } else {
            // Pending mission data present: create specific mission from data
            undefined4 *missionData = (undefined4 *)FUN_00446130(&a, 0); // Parse mission spawn data
            undefined4 *pool2 = (undefined4 *)FUN_009c8f80();
            int newMission2 = 0;
            undefined4 allocParams2[3] = {2, 0x10, 0};
            int mem2 = (**(code **)*pool2)(0x1c0, &allocParams2);
            if (mem2 != 0) {
                newMission2 = FUN_006db0c0(missionData);            // Construct mission from data
            }
            if (*pendingMissionsHead != newMission2) {
                if (*pendingMissionsHead != 0) {
                    FUN_004daf90(pendingMissionsHead);
                }
                *pendingMissionsHead = newMission2;
                if (newMission2 != 0) {
                    *(int *)((int)thisPtr + 0x84) = *(int *)(newMission2 + 4);
                    *(int **)(newMission2 + 4) = pendingMissionsHead;
                }
            }
            if (missionData != 0) {
                (**(code **)*missionData)(1);                       // Release mission data?
            }
        }
        FUN_00424ea0(*(undefined4 *)(&DAT_00002494 + *(int *)((int)thisPtr + 0x58)), *pendingMissionsHead, 0); // Schedule pending mission activation?
    }

    int isPaused = FUN_00800a90();                                   // Check if game is paused
    bool bVar4;
    if (isPaused == 0 || ((*(unsigned int *)(gameManagerPtr + 0x8e0) >> 10 & 1) == 0)) {
        bVar4 = false;
    } else {
        bVar4 = true;                                                // Game is paused and flag bit 10 set?
    }

    if (*(int *)(gameManagerPtr + 0x8e8) < 0 && !bVar4) {
        char canUpdate = FUN_0079ebe0(1);                            // Some condition check
        if (canUpdate != '\0') {
            if (DAT_01205228 - *(float *)((int)thisPtr + 0xc0) < *(float *)(gameManagerPtr + 0x2024)) {
                return;                                              // Not enough time elapsed
            }
            FUN_0079dbf0();                                          // Perform update action
        }
    }
    *(float *)((int)thisPtr + 0xc0) = DAT_01205228;                 // Store current time for delta check
    return;
}