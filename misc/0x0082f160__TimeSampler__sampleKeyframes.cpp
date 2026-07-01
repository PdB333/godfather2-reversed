// FUNC_NAME: TimeSampler::sampleKeyframes
undefined4* __thiscall TimeSampler::sampleKeyframes(
    TimeSampler *this,
    undefined4 *outResult,
    TimeInput *timeInput,
    uint *outIndices
)
{
    uint currentIndex;
    uint nextIndex;
    int keyframeCurrent;
    int keyframeNext;
    uint currentTimeSeconds;
    uint nextTimeSeconds;
    uint inputTimeSeconds;
    int diffNext;
    int diffInput;
    float blend;
    float blendAbs;
    float fDiffInput;
    float fDiffNext;
    uint uVar1;
    uint uVar2;
    int iVar3;
    int iVar4;
    float fVar5;
    float fVar6;
    float fVar11;
    undefined *local_90[20]; // sized enough for internal usage
    undefined4 local_8c;
    undefined4 local_88;
    undefined4 local_84;
    undefined4 local_80;
    undefined4 local_7c;
    undefined4 local_78;
    // default blend values
    float defaultBlend = _DAT_00d5780c; // 0.0f or identity value
    float defaultResult[8];
    for(int i=0;i<8;i++) defaultResult[i] = defaultBlend;

    // find keyframe index for given time
    currentIndex = FUN_0082c4d0(timeInput); // binary search?
    if (currentIndex == 0xFFFFFFFF) {
        if (outIndices != nullptr) {
            outIndices[0] = 0xFFFFFFFF;
            outIndices[1] = 0xFFFFFFFF;
            outIndices[2] = 0;
        }
        FUN_008334a0(); // set default values perhaps
        // fill outResult with defaults
        outResult[0] = (undefined4)&PTR_LAB_00d73454; // vtable/type?
        outResult[0x14] = DAT_00d5d7b8;
        outResult[0x15] = DAT_00e44620;
        outResult[0x16] = DAT_00d5ef88;
        outResult[0x17] = DAT_00e44980;
        for(int i=0;i<8;i++) outResult[0x18+i] = defaultResult[i];
        return outResult;
    }

    this->m_currentIndex = currentIndex;

    // next keyframe (wrap around)
    if (currentIndex < (uint)(this->m_keyframeCount - 1)) {
        nextIndex = currentIndex + 1;
    } else {
        nextIndex = 0;
    }

    keyframeCurrent = this->m_keyframeArray[currentIndex];
    keyframeNext = this->m_keyframeArray[nextIndex];

    // convert keyframe times to total seconds
    // keyframe offset: +0x10=hour, +0x14=minute, +0x18=second
    currentTimeSeconds = *(int*)(keyframeCurrent + 0x18) +
        (*(int*)(keyframeCurrent + 0x14) + *(int*)(keyframeCurrent + 0x10) * 60) * 60;

    // input time: timeInput[3]=hour, [4]=minute, [5]=second
    inputTimeSeconds = timeInput->seconds + (timeInput->minutes + timeInput->hours * 60) * 60;

    if (nextIndex == 0) {
        // wrapped around: need to handle day boundary
        nextTimeSeconds = *(int*)(keyframeNext + 0x18) +
            (*(int*)(keyframeNext + 0x14) + *(int*)(keyframeNext + 0x10) * 60) * 60
            + (86400 - currentTimeSeconds); // 24h in seconds
        if (inputTimeSeconds < currentTimeSeconds) {
            diffInput = inputTimeSeconds + (86400 - currentTimeSeconds);
        } else {
            diffInput = inputTimeSeconds - currentTimeSeconds;
        }
    } else {
        nextTimeSeconds = *(int*)(keyframeNext + 0x18) +
            (*(int*)(keyframeNext + 0x14) + *(int*)(keyframeNext + 0x10) * 60) * 60;
        diffInput = (int)(inputTimeSeconds - currentTimeSeconds);
    }

    diffNext = (int)(nextTimeSeconds - currentTimeSeconds); // seconds between keyframes

    if (diffNext == 0) {
        if (outIndices != nullptr) {
            outIndices[0] = currentIndex;
            outIndices[1] = nextIndex;
            outIndices[2] = (uint)defaultBlend;
        }
        FUN_00825640(keyframeNext); // copy keyframe data? apply keyframe
    } else {
        fDiffInput = (float)diffInput;
        if (diffInput < 0) {
            fDiffInput = fDiffInput + _DAT_00e44578; // adjust for wrap?
        }
        fDiffNext = (float)diffNext;
        if (diffNext < 0) {
            fDiffNext = fDiffNext + _DAT_00e44578; // shouldn't happen normally
        }
        blend = fDiffInput / fDiffNext;
        if (outIndices != nullptr) {
            blendAbs = defaultBlend - blend;
            outIndices[0] = currentIndex;
            outIndices[1] = nextIndex;
            outIndices[2] = *(uint*)&blendAbs;
        }
        FUN_0082b2b0(&local_90, blend, keyframeCurrent, keyframeNext); // interpolate
    }

    // copy timeInput fields to local stack for later use (preserve)
    local_8c = ((undefined4*)timeInput)[0];
    local_88 = ((undefined4*)timeInput)[1];
    local_84 = ((undefined4*)timeInput)[2];
    local_80 = ((undefined4*)timeInput)[3];
    local_7c = ((undefined4*)timeInput)[4];
    local_78 = ((undefined4*)timeInput)[5];

    FUN_00825640(&local_90); // finalize output into outResult? Or store?
    // Actually the final call might copy the interpolated result to outResult
    // but the decompiled code shows it returns param_2

    return outResult;
}