// Xbox PDB: EARS_Apt_UIJobInfo_ManipulateEffect
// FUNC_NAME: MissionManager::checkMissionDialog
// Address: 0x00950be0
// Role: Checks if a mission dialog can be triggered based on current state and dialog ID

bool __thiscall MissionManager::checkMissionDialog(int thisPtr, char allowDialog, int dialogId)
{
    int missionType; // +0x54
    int currentDialogId; // +0x164
    int dialogPlayedFlag; // +0x17c
    undefined4* missionTargetData;
    undefined4 local_54[3]; // used for transform
    undefined4 local_68[3];
    undefined4 local_7c[3];
    undefined4 local_90[3];
    undefined4 local_84, local_80, local_88, local_8c;
    undefined4 local_74, local_6c, local_70, local_78;
    undefined4 local_64;
    undefined4 local_60[3]; // target position/rotation
    undefined1 local_50[52]; // resulting dialog transform data
    float local_1c;
    undefined4 local_94; // dialog entity handle
    char* dialogName;

    if (allowDialog == '\0') {
        // If dialog not allowed, reset and return true
        resetMissionDialog();
        return true;
    }

    // Check if the dialog ID matches the current mission dialog ID
    if ((dialogId != *(int*)(thisPtr + 0x164)) ||
        (missionTargetData = (undefined4*)getMissionTargetData(), missionTargetData == (undefined4*)0x0)) {
        return false;
    }

    // Initialize transform components with default values
    local_54[0] = _DAT_00d5780c;
    local_68[0] = _DAT_00d5780c;
    local_7c[0] = _DAT_00d5780c;
    local_90[0] = _DAT_00d5780c;
    local_84 = 0;
    local_80 = 0;
    local_88 = 0;
    local_8c = 0;
    local_74 = 0;
    local_6c = 0;
    local_70 = 0;
    local_78 = 0;
    local_64 = 0;
    local_60[0] = *missionTargetData;
    local_60[1] = missionTargetData[1];
    local_60[2] = missionTargetData[2];

    // Compute dialog transform from mission target data
    computeMissionDialogTransform(local_50, (undefined4*)&local_90);

    // Accumulate time (likely for animation blending)
    local_1c = local_1c + DAT_00d8bbc8;

    // Reset mission dialog state
    resetMissionDialog();

    // Determine dialog name based on mission type
    missionType = *(int*)(thisPtr + 0x54);
    if (missionType == 5) {
        dialogName = "dv_job_giver";
    }
    else if ((missionType == 0) || (missionType == 1)) {
        dialogName = "dv_mission_task";
    }
    else {
        dialogName = (char*)getCustomMissionDialog();
        if (dialogName == (char*)0x0) {
            return false;
        }
    }

    // Create dialog entity with given parameters
    undefined4 result = FUN_0045c740(&local_94, dialogName, local_50, 0x2ff, 4, 0, 0xffffffff, 0);
    // Set dialog entity callback
    FUN_00414db0(result);
    if (local_94 != 0) {
        // Clear some field at offset +8
        *(undefined4*)(local_94 + 8) = 0;
    }

    // Return whether the dialog has been played
    return *(int*)(thisPtr + 0x17c) != 0;
}