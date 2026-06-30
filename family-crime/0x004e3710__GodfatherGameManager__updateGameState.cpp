// FUNC_NAME: GodfatherGameManager::updateGameState
void GodfatherGameManager::updateGameState(int state) {
    uint flags;
    bool bVar2;
    bool bVar3;
    bool bVar4;
    bool bVar5;
    bool bVar6;
    bool bVar7;
    char cVar8;
    char cVar9;
    undefined1 uVar10;
    undefined1 uVar11;
    undefined1 uVar12;
    undefined1 uVar13;
    int iVar14;
    undefined4 uVar15;

    uVar12 = 0;
    if (state >= 0) {
        if (state == 1) {
            // State 1: Game is running
            FUN_00531d40(); // updateAudioDataManager
            if (DAT_01194740 == '\0') {
                FUN_0052fe10(); // updateBuildingManager
            }
            if (DAT_01194739 == '\0') {
                FUN_005167d0(); // updateFamilyManager
            }
            cVar8 = DAT_012054fd; // some flag
            cVar9 = '\0';
            uVar15 = 0;
            uVar10 = 0;
            uVar11 = 0;
            uVar13 = 0;
            if (DAT_0119473a == '\0') {
                cVar9 = FUN_00515a20(); // checkDialogTreeManager
                if (cVar9 != '\0') {
                    if ((DAT_0121922c < DAT_00e2af44) ||
                       (((DAT_01219210 < DAT_00e2af44 && (DAT_01219214 < DAT_00e2af44)) &&
                        (DAT_01219218 < DAT_00e2af44)))) {
                        uVar15 = 1;
                    }
                    else {
                        uVar15 = 0;
                    }
                }
            }
            if (DAT_01194743 == '\0') {
                FUN_0052ea40(); // updateChaseManager
            }
            if (DAT_01194748 == '\0') {
                uVar10 = FUN_00527e20(); // updatePlayerActionableInfo
            }
            if (DAT_0119473f == '\0') {
                uVar11 = FUN_00531280(); // updateTargetingManager
            }
            if (DAT_0119473c == '\0') {
                uVar12 = FUN_00517970(); // updateCombatKnowledge
            }
            if (DAT_01194745 == '\0') {
                uVar13 = FUN_0052a120(); // updateVehicleBrain
            }
            iVar14 = FUN_0052de20(cVar9, uVar15, uVar10, uVar11, uVar12, uVar13); // evaluateGameState
            flags = (&DAT_01198ee8)[iVar14 * 0x1b]; // get flags from table
            if ((DAT_0119473c != '\0') || (bVar5 = false, (flags >> 5 & 1) != 0)) {
                bVar5 = true;
            }
            if ((DAT_0119473a != '\0') || (bVar3 = false, (flags >> 2 & 1) != 0)) {
                bVar3 = true;
            }
            if ((DAT_01194748 != '\0') || (bVar6 = false, (flags >> 4 & 1) != 0)) {
                bVar6 = true;
            }
            if ((DAT_0119473f != '\0') || (bVar7 = false, (flags & 1) != 0)) {
                bVar7 = true;
            }
            if ((DAT_01194743 == '\0') || (bVar4 = true, (flags & 0xfffff8ff) != 0)) {
                bVar4 = false;
            }
            if ((flags == 0) || (cVar8 == '\0')) {
                bVar2 = false;
            }
            else {
                bVar2 = true;
            }
            if ((DAT_01194745 == '\0') && ((flags >> 1 & 1) == 0)) {
                FUN_0052a260(); // updateVehicleBrainIdle
            }
            if ((!bVar2) && (DAT_012054fd != '\0')) {
                FUN_0052b390(0x3f800000); // setTimeScale(1.0f)
            }
            if ((flags >> 5 & 1) != 0) {
                FUN_00517b10(); // updateCombatPerception
            }
            if (DAT_0119473a == '\0') {
                FUN_00515a80(param_1, flags >> 5 & 0xffffff01); // updateDialogTreeManager
            }
            if (!bVar3) {
                FUN_00515c20(); // updateDialogTreeManagerPost
            }
            if (!bVar4) {
                FUN_0052f250(param_1, flags, cVar8); // updateChaseManagerPost
            }
            if (!bVar5) {
                FUN_00517de0(param_1); // updateCombatKnowledgePost
            }
            if (!bVar6) {
                FUN_00527e60(); // updatePlayerActionableInfoPost
            }
            if (!bVar7) {
                FUN_005312d0(); // updateTargetingManagerPost
            }
            if (DAT_01194746 == '\0') {
                FUN_0052b990(); // updateTrafficManager
            }
            if (DAT_01194747 == '\0') {
                FUN_005262b0(); // updateNPCManager
                return;
            }
        }
        else if ((state == 0) && (DAT_0119473b == '\0')) {
            FUN_004e6e30(); // initializeGameState
            return;
        }
    }
    return;
}