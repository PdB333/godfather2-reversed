// FUNC_NAME: AnimationBlendController::updateBlend

void __thiscall AnimationBlendController::updateBlend(int thisPtr, float time)
{
    undefined4 *trackA; // pointer to first animation track
    undefined4 *trackB; // pointer to second animation track
    int durationA;      // duration or weight of track A
    int durationB;      // duration or weight of track B
    int maxDuration;
    undefined8 local_18;
    uint local_10;
    undefined4 local_c;
    undefined8 *local_8;
    undefined1 local_4;

    trackA = (undefined4 *)(thisPtr + 0x290);
    if (*(int *)(thisPtr + 0x290) == 0) {
        durationA = 100; // default duration if track A is null
    } else {
        durationA = *(int *)(thisPtr + 0x298); // +0x298: duration/weight of track A
    }

    trackB = (undefined4 *)(thisPtr + 0x29c);
    if (*(int *)(thisPtr + 0x29c) == 0) {
        durationB = 0; // default duration if track B is null
    } else {
        durationB = *(int *)(thisPtr + 0x2a4); // +0x2a4: duration/weight of track B
    }

    if (durationA < durationB) {
        durationA = durationB;
    }
    maxDuration = durationA;

    // Check if we should use track A or track B based on time
    if ((((float)maxDuration <= time) || (time < (float)durationB)) || (*(int *)(thisPtr + 0x290) == 0)) {
        // Use track B (or fallback)
        if (((float)durationB <= time) || (*(int *)(thisPtr + 0x29c) == 0)) {
            goto LAB_008ba10f;
        }
        // Set up local structure for track B release
        local_18._4_4_ = (undefined4 *)(thisPtr + 0x48); // +0x48: some pointer
        local_18._0_4_ = &PTR_FUN_00e31e2c; // vtable pointer
        local_10 = 0;
        if (local_18._4_4_ != (undefined4 *)0x0) {
            local_10 = *(uint *)(thisPtr + 0x4c); // +0x4c: some count
            *(int *)(thisPtr + 0x4c) = (int)&local_18 + 4;
        }
        local_c = *trackB;
        local_8 = &local_18;
        local_4 = 0;
        FUN_00408a00(&local_c, 0); // release track B
        FUN_00408310(trackB);      // clear track B pointer
        *trackB = 0;
        if (local_18._4_4_ == (undefined4 *)0x0) {
            goto LAB_008ba10f;
        }
        ppuVar4 = (undefined8 **)((int)&local_18 + 4);
    } else {
        // Use track A
        FUN_0045ca00(thisPtr); // update track A blend
        local_18._0_4_ = (undefined **)*trackA;
        local_18._4_4_ = &local_c;
        local_10 = local_10 & 0xffffff00;
        FUN_00408a00(&local_18, 0); // release track A
        FUN_00408310(trackA);      // clear track A pointer
        *trackA = 0;
        if (local_8 == (undefined8 *)0x0) {
            goto LAB_008ba10f;
        }
        ppuVar4 = &local_8;
    }
    FUN_004daf90(ppuVar4); // delete the temporary structure

LAB_008ba10f:
    // Fire animation event callback if present
    if (*(int **)(thisPtr + 0x130) != (int *)0x0) { // +0x130: event handler pointer
        local_18 = (longlong)ROUND(time + _DAT_00d5c458); // global time offset
        (**(code **)(**(int **)(thisPtr + 0x130) + 0x44))(0xa500bcbc, (undefined **)local_18); // vtable+0x44: event callback
    }
    return;
}