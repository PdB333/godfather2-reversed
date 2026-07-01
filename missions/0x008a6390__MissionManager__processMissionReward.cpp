// FUNC_NAME: MissionManager::processMissionReward
void MissionManager::processMissionReward(int thisPtr, undefined4 *rewardData, undefined4 *extraData) {
    int missionState;
    undefined4 uVar2;
    undefined4 uVar3;
    undefined4 uVar4;
    undefined4 uVar5;
    int *piVar6;
    undefined4 uVar7;
    undefined4 uVar8;
    int local_10 [3];
    code *local_4;

    if (rewardData == (undefined4 *)0x0) {
        return;
    }
    uVar8 = rewardData[2]; // +0x8: reward type / ID
    uVar7 = *rewardData; // +0x0: reward value or pointer
    missionState = *(int *)(thisPtr + 4); // +0x4: current mission state
    if (missionState != 0x28) { // MISSION_STATE_REWARD_INVALID?
        if ((((missionState != 0x29) && (missionState != 0x2a)) && (missionState != 0x2b)) && (missionState != 0x2c)) {
            // Not a standard reward state - handle custom reward
            FUN_004d3bc0(0); // maybe beginAudioSequence
            if (extraData != (undefined4 *)0x0) {
                uVar2 = *extraData; // +0x0
                uVar3 = FUN_004baf90(*(undefined4 *)(thisPtr + 0x14)); // get character entity +0x14
                uVar3 = FUN_004bb600(uVar3); // convert to string/ID
                FUN_004d3e20(uVar3); // playAudioLine
                uVar3 = extraData[2]; // +0x8
                uVar4 = FUN_008a6010(thisPtr); // get mission-specific data
                piVar6 = local_10;
                uVar5 = FUN_004bb600(rewardData); // serialize rewardData
                FUN_0094e490(uVar8, uVar5, uVar3, piVar6, uVar7, uVar2, uVar4); // displayRewardUI
            }
            if (local_10[0] == 0) {
                return;
            }
            (*local_4)(local_10[0]); // call callback function
            return;
        }
        if (((missionState != 0x28) && (missionState != 0x29)) &&
           ((missionState != 0x2a && ((missionState != 0x2b && (missionState != 0x2c)))))) {
            missionState = -1;
        }
    }
    // Standard monetary/item reward state (0x28-0x2c)
    uVar8 = *(undefined4 *)(thisPtr + 0xc); // +0xc: reward amount or item index
    uVar2 = FUN_004bb600(rewardData); // serialize
    FUN_0094e520(uVar2, uVar7, missionState, uVar8); // applyStandardReward
    return;
}