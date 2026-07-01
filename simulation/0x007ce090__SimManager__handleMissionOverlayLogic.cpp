// FUNC_NAME: SimManager::handleMissionOverlayLogic
void __fastcall SimManager::handleMissionOverlayLogic(int this)
{
    int *gameStatePtr; // piVar4
    int *local4; // local_4
    uint local_8; // local_8
    int vftable; // *gameStatePtr
    char isUpdated; // cVar3
    int iVar5; // iVar5
    int iVar7; // iVar7
    uint ebxBackup; // unaff_EBX

    int *missionManager = *(int **)(this + 0x58); // +0x58: pointer to MissionManager
    gameStatePtr = (int *)FUN_007ab690(); // likely GameStateManager::getInstance()
    local4 = gameStatePtr;
    if (gameStatePtr != (int *)0x0) {
        uint currentTime = *(uint *)(this + 0x1d0); // +0x1d0: some time or flag
        local_8 = 0;
        isUpdated = (**(code **)(*gameStatePtr + 0x10))(0x55859efa, &local_8); // likely GameState::query some flag
        isUpdated = FUN_007cbcd0(*missionManager, -(uint)(isUpdated != '\0') & local_8, 1, currentTime); // check if update needed
        if (isUpdated != '\0') goto LAB_007ce1c4;
    }
    int *overlayData = (int *)(this + 0x11c); // +0x11c: overlay data pointer
    if (*(int *)(this + 0x11c) != 0) {
        FUN_004daf90(overlayData); // free memory
        *overlayData = 0;
    }
    undefined4 *overlayActive = (undefined4 *)(this + 0xa0); // +0xa0: overlay active flag
    *overlayActive = 1;
    *(undefined4 *)(this + 0x110) = 0; // +0x110: some counter
    *(undefined4 *)(this + 400) = *(undefined4 *)(*missionManager + 0x3180); // copy mission data
    FUN_0081b030(*missionManager, overlayActive, 0); // start overlay
    FUN_0081db00(overlayActive); // overlay update callback

    if (*overlayData == 0) {
        gameStatePtr = (int *)0x0;
    }
    else {
        gameStatePtr = (int *)(*overlayData - 0x48); // adjust pointer (likely offset)
        if (gameStatePtr != (int *)0x0) {
            uint time2 = *(uint *)(this + 0x1d0);
            local_8 = 0;
            isUpdated = (**(code **)(*gameStatePtr + 0x10))(0x55859efa, &local_8);
            isUpdated = FUN_007cbcd0(*missionManager, -(uint)(isUpdated != '\0') & local_8, 1, time2);
            if (isUpdated != '\0') goto LAB_007ce1c4;
        }
    }
    iVar5 = FUN_00625050(0xc4bc3ce7, 0); // look up some mod object
    if (iVar5 != 0) {
        gameStatePtr = (int *)FUN_007e3640(local4, gameStatePtr); // create mod instance
    }

LAB_007ce1c4:
    int *someSlot = (int *)(this + 0x1b4); // +0x1b4: slot for dynamic object
    iVar5 = 0;
    if (gameStatePtr != (int *)0x0) {
        local_8 = 0;
        isUpdated = (**(code **)(*gameStatePtr + 0x10))(0x55859efa, &local_8);
        uint condition = -(uint)(isUpdated != '\0') & ebxBackup;
        if (condition != 0) {
            iVar5 = condition + 0x48; // add offset 0x48 (likely size of object)
        }
        if (*someSlot != iVar5) {
            if (*someSlot != 0) {
                FUN_004daf90(someSlot); // free previous slot data
            }
            *someSlot = iVar5;
            if (iVar5 != 0) {
                *(undefined4 *)(this + 0x1b8) = *(undefined4 *)(iVar5 + 4); // store next pointer
                *(int **)(iVar5 + 4) = someSlot; // link back
            }
        }
        if ((*someSlot != 0) && (*someSlot != 0x48)) {
            FUN_00716c50(*missionManager); // some mission manager update
            if (*someSlot == 0) {
                iVar5 = 0;
            }
            else {
                iVar5 = *someSlot - 0x48; // adjust pointer to base object
            }
            *(undefined4 *)(this + 0x1bc) = *(undefined4 *)(iVar5 + 0x1f3c); // copy another field
            if (*someSlot == 0) {
                iVar7 = 0;
            }
            else {
                iVar7 = *someSlot - 0x48;
            }
            isUpdated = FUN_007cbcd0(*missionManager, iVar7, 1, *(undefined4 *)(this + 0x1d0));
            if (isUpdated != '\0') {
                FUN_0072fec0(1); // set some flag
                int iVar8 = FUN_007f41e0(); // get player controller
                if (iVar8 != 0) {
                    *(uint *)(this + 0x1d0) |= 5; // set bits
                    FUN_004abc40(8, 0); // post UI event
                }
                FUN_007cb210(iVar5); // handle completion
                return;
            }
            if (*someSlot != 0) {
                FUN_004daf90(someSlot); // cleanup
                *someSlot = 0;
            }
        }
    }
    return;
}