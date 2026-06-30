// FUNC_NAME: GodfatherGameManager::startScenario
void GodfatherGameManager::startScenario(float timeThreshold, uint missionId, bool isNewGame) {
    int iVar1;
    uint uVar2;
    uint uVar3;
    uint in_EAX; // currentMissionId
    uint uVar4;
    undefined4 *puVar5;
    uint missionListIndex;
    float fVar7;
    
    if (missionId == 0) {
        // Default mission ID based on new game flag
        missionId = gScenarioTimeThresholds[(-((uint)(isNewGame != false) & 0xfffffffd)) * 2];
    }
    
    fVar7 = gDefaultTimeMin;
    if (isNewGame != false) {
        fVar7 = gNewGameTimeMin;
    }
    
    missionListIndex = gScenarioTimeThresholds[(-((uint)(isNewGame != false) & 0xfffffffd)) * 2];
    
    // Check if we need to start scenario (time elapsed or mission changed)
    if ((0.0 < timeThreshold - fVar7) || (missionListIndex = missionId, missionId != in_EAX)) {
        // Clean up previous mission state
        if ((in_EAX != 0xffffffff) && (in_EAX < 0x1000)) {
            iVar1 = in_EAX * 0x38;
            if ((&gActiveMissionArray + iVar1 != (byte *)0x0) && 
                ((byte)(&gActiveMissionArray)[iVar1] < 4)) {
                if (*(int *)(&gActiveMissionData + iVar1) != 0) {
                    FUN_00606e60(*(int *)(&gActiveMissionData + iVar1), 0x100000);
                }
                *(uint *)(&gActiveMissionFlags + iVar1) = 
                    *(uint *)(&gActiveMissionFlags + iVar1) & 0xfc9c8fff | 0x100000;
                FUN_006189c0();
            }
        }
        
        // Find mission in global list and clear active flag
        uVar4 = 0;
        do {
            if ((&gMissionList)[uVar4 * 2] == missionListIndex) {
                if (uVar4 < 0x14) {
                    (&gMissionListActive)[uVar4 * 2] = (&gMissionListActive)[uVar4 * 2] & 0xfffffffc;
                }
                break;
            }
            uVar4 = uVar4 + 1;
        } while (uVar4 < 0x14);
        
        uVar2 = gPrevMissionId;
        uVar4 = gPreviousActiveMission;
        gPrevMissionId = 0;
        gPreviousActiveMission = missionListIndex;
        
        // Update audio/rendering system
        FUN_00609340(0, uVar4, uVar2);
        FUN_00609810(1);
        FUN_0060db60(0, 0, 0, 0x3f800000, 0x3f800000);
        
        // Clamp and set day/night cycle limits
        if (gMinTimeOfDay < 0x16) {
            gMinTimeOfDay = 0x16;
        }
        if (0x16 < gMaxTimeOfDay) {
            gMaxTimeOfDay = 0x16;
        }
        gDayNightFlags = 1;
        if (gMinTimeOfDay < 0xe) {
            gMinTimeOfDay = 0xe;
        }
        if (0xe < gMaxTimeOfDay) {
            gMaxTimeOfDay = 0xe;
        }
        gDayNightFlags2 = 0;
        if (gMinTimeOfDay < 7) {
            gMinTimeOfDay = 7;
        }
        if (7 < gMaxTimeOfDay) {
            gMaxTimeOfDay = 7;
        }
        gDayNightFlags3 = 0;
        if (gMinTimeOfDay < 0x19) {
            gMinTimeOfDay = 0x19;
        }
        if (0x19 < gMaxTimeOfDay) {
            gMaxTimeOfDay = 0x19;
        }
        gDayNightFlags4 = 5;
        if (gMinTimeOfDay < 0x18) {
            gMinTimeOfDay = 0x18;
        }
        if (0x18 < gMaxTimeOfDay) {
            gMaxTimeOfDay = 0x18;
        }
        gDayNightFlags5 = 0;
        if (gMinTimeOfDay < 0xf) {
            gMinTimeOfDay = 0xf;
        }
        if (0xf < gMaxTimeOfDay) {
            gMaxTimeOfDay = 0xf;
        }
        gDayNightFlags6 = 0;
        
        // UI update
        FUN_00417cf0(1, 2, 1);
        
        if (gMinTimeOfDay < 0x1b) {
            gMinTimeOfDay = 0x1b;
        }
        if (0x1a < gMaxTimeOfDay) {
            gMaxTimeOfDay = 0x1b;
        }
        gDayNightFlags7 = 0;
        
        // Swap audio/environment data
        gAudioData1 = gAudioData2;
        gAudioData3 = gAudioData4;
        gAudioParam1 = 5;
        
        if (gAudioCallback == &gAudioData2) {
            FUN_0060a460(gAudioData2);
            FUN_0060a460(gAudioData3);
        }
        
        // Update AI, camera, effects
        FUN_00530a60();
        FUN_00530df0();
        FUN_00530ff0();
        
        // Allocate and initialize sound parameters
        puVar5 = (undefined4 *)FUN_0060cd00(0xd, 4, 0, 1, 0);
        if (puVar5 != (undefined4 *)0x0) {
            *puVar5 = gSoundParam1;
            puVar5[1] = gSoundParam2;
            puVar5[2] = 0;
            puVar5[3] = 0;
            puVar5[4] = gSoundParam2;
            puVar5[5] = gSoundParam2;
            puVar5[6] = gSoundParam2;
            puVar5[7] = 0;
            puVar5[8] = gSoundParam2;
            puVar5[9] = gSoundParam1;
            puVar5[10] = gSoundParam2;
            puVar5[0xb] = gSoundParam2;
            puVar5[0xc] = gSoundParam1;
            puVar5[0xd] = gSoundParam1;
            puVar5[0xe] = 0;
            puVar5[0xf] = gSoundParam2;
            FUN_0060cde0();
        }
        
        FUN_00612e00();
        gAudioData3 = 0;
        gAudioData1 = 0;
        gAudioCallback2 = 0;
        gAudioCallback3 = 0;
        FUN_00609890(1);
        FUN_0052c420(missionListIndex, missionId);
    }
    return;
}