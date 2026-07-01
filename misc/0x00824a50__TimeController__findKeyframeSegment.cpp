// FUNC_NAME: TimeController::findKeyframeSegment
undefined4 __thiscall TimeController::findKeyframeSegment(int thisPtr, undefined4 retParam, uint *inputTime, uint *outKeyframes)
{
    uint currentIdx;
    uint nextIdx;
    int iVar3;
    int iVar4;
    float fVar5;
    float fVar6;
    uint uVar7;
    int iVar8;
    uint uVar9;
    int iVar10;
    float fVar11;
    void *local_80;
    undefined4 local_7c;
    undefined4 local_78;
    undefined4 local_74;
    undefined4 local_70;
    undefined4 local_6c;
    undefined4 local_68;
    undefined4 local_34;
    undefined4 local_30;
    undefined4 local_2c;
    undefined4 local_28;
    int local_24[2];
    float local_1c;
    
    // Find index of keyframe that matches the input time exactly (or closest)
    uVar7 = FUN_00824620(inputTime);
    if (uVar7 == 0xffffffff) {
        if (outKeyframes != (uint *)0x0) {
            *outKeyframes = 0xffffffff;
            outKeyframes[1] = 0xffffffff;
            outKeyframes[2] = 0;
        }
        FUN_008334a0();
        local_80 = &PTR_FUN_00d7343c;
        local_34 = 0;
        local_30 = 0;
        local_2c = 0;
        local_28 = 0;
        local_24[0] = 0;
        local_24[1] = 0;
        local_1c = _DAT_00d5780c;
        FUN_00824870(&local_80);
        local_80 = &PTR_FUN_00d7343c;
        if (local_24[0] != 0) {
            FUN_004daf90(local_24);
        }
        return retParam;
    }
    // Store found index
    *(uint *)(thisPtr + 4) = uVar7;
    fVar5 = _DAT_00d5780c;
    // Determine next index (wrapping around)
    if (uVar7 < *(int *)(thisPtr + 0xc) - 1U) {
        uVar9 = uVar7 + 1;
    } else {
        uVar9 = 0;
    }
    // Retrieve keyframe pointers for current and next
    iVar3 = *(int *)(*(int *)(thisPtr + 8) + uVar7 * 4);
    iVar4 = *(int *)(*(int *)(thisPtr + 8) + uVar9 * 4);
    // Convert current keyframe time to total seconds (hour*3600 + minute*60 + second)
    uVar1 = *(int *)(iVar3 + 0x18) + (*(int *)(iVar3 + 0x14) + *(int *)(iVar3 + 0x10) * 0x3c) * 0x3c;
    if (uVar9 == 0) {
        // If next index wrapped, compute time difference with day wrap (86400 seconds)
        uVar2 = inputTime[5] + (inputTime[4] + inputTime[3] * 0x3c) * 0x3c;
        iVar8 = *(int *)(iVar4 + 0x18) + (*(int *)(iVar4 + 0x14) + *(int *)(iVar4 + 0x10) * 0x3c) * 0x3c
                + (0x15180 - uVar1);
        if (uVar2 < uVar1) {
            iVar10 = uVar2 + (0x15180 - uVar1);
        } else {
            iVar10 = uVar2 - uVar1;
        }
    } else {
        // Normal case: compute time difference between input and current keyframe
        iVar10 = ((inputTime[4] + inputTime[3] * 0x3c) * 0x3c - uVar1) + inputTime[5];
        iVar8 = (*(int *)(iVar4 + 0x18) +
                (*(int *)(iVar4 + 0x14) + *(int *)(iVar4 + 0x10) * 0x3c) * 0x3c) - uVar1;
    }
    if (iVar8 == 0) {
        // If time difference is zero, set exact indices and full blend factor (1.0)
        if (outKeyframes != (uint *)0x0) {
            *outKeyframes = uVar7;
            outKeyframes[1] = uVar9;
            outKeyframes[2] = (uint)fVar5;
        }
        FUN_00824870(iVar4);
    } else {
        // Compute blend factor (t = timeSinceLastKeyframe / intervalDuration)
        fVar5 = (float)iVar10;
        if (iVar10 < 0) {
            fVar5 = fVar5 + DAT_00e44578;
        }
        fVar6 = (float)iVar8;
        if (iVar8 < 0) {
            fVar6 = fVar6 + DAT_00e44578;
        }
        if (outKeyframes != (uint *)0x0) {
            fVar11 = _DAT_00d5780c - fVar5 / fVar6;
            // Output: previous keyframe index, next keyframe index, blend factor (0..1)
            *outKeyframes = uVar7;
            outKeyframes[1] = uVar9;
            outKeyframes[2] = (uint)fVar11;
        }
        // Call interpolation function with blend factor and both keyframes
        FUN_008248d0(&local_80, fVar5 / fVar6, iVar3, iVar4);
    }
    // Copy input time struct for debugging/reference
    if (&local_7c != inputTime) {
        local_7c = *inputTime;
        local_74 = inputTime[2];
        local_78 = inputTime[1];
        local_70 = inputTime[3];
        local_68 = inputTime[5];
        local_6c = inputTime[4];
    }
    FUN_00824870(&local_80);
    local_80 = &PTR_FUN_00d7343c;
    if (local_24[0] != 0) {
        FUN_004daf90(local_24);
    }
    return retParam;
}