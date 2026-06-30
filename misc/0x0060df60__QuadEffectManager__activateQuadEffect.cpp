// FUNC_NAME: QuadEffectManager::activateQuadEffect
void __fastcall QuadEffectManager::activateQuadEffect(undefined4 param_1, undefined4 param_2, uint effectIndex, uint targetIndex)
{
    undefined4 savedParam2;
    undefined4 savedTargetIndex;
    undefined4 uVar1;
    undefined4 uVar2;
    undefined4 uVar3;
    undefined4 uVar4;
    undefined4 uVar5;
    undefined4 uVar6;
    undefined4 uVar7;
    uint uVar8;
    undefined4 uVar9;
    int iVar10;
    undefined4 *puVar11;
    undefined1 *effectData;
    int *effectPtr;

    uVar9 = DAT_011f38f4; // saved param_2
    uVar6 = DAT_011f38f0; // saved target index

    // Validate effect index and check if effect is active (bit 3 of flags at +0x0C)
    if (effectIndex < 0x1000) {
        effectData = &DAT_011a0f28 + effectIndex * 0x38; // 0x38 bytes per effect entry
    } else {
        effectData = (undefined1 *)0x0;
    }
    if ((effectData[0xc] & 8) != 0) {
        // If effect is active, check target
        if (targetIndex < 0x1000) {
            effectData = &DAT_011a0f28 + targetIndex * 0x38;
        } else {
            effectData = (undefined1 *)0x0;
        }
        if ((effectData[0xc] & 8) == 0) {
            FUN_00618b80(); // deactivate effect
            return;
        }
    }

    // Save current camera state (position/rotation at DAT_011f3918 + slot*0x18)
    uVar1 = *(undefined4 *)(&DAT_011f3918 + DAT_012058b0 * 0x18);
    iVar10 = DAT_012058b0 * 0x18;
    uVar2 = *(undefined4 *)(&DAT_011f391c + iVar10);
    uVar3 = *(undefined4 *)(&DAT_011f3920 + iVar10);
    uVar4 = *(undefined4 *)(&DAT_011f3924 + iVar10);

    // Set new target and param
    DAT_011f38f0 = targetIndex;
    DAT_011f38f4 = param_2;

    // Setup effect parameters
    FUN_00609340(0, uVar6, uVar9); // set previous camera
    FUN_0060db60(0, 0, 0, 0x3f800000, 0x3f800000); // set scale (1.0, 1.0)
    FUN_00609810(1); // enable effect

    // Find effect class by name "SM_QuadEffectClass"
    iVar10 = FUN_0060d740("SM_QuadEffectClass");
    for (effectPtr = DAT_012058ec; effectPtr != (int *)0x0; effectPtr = (int *)effectPtr[1]) {
        if (iVar10 == effectPtr[2]) goto LAB_0060e072;
    }
    effectPtr = (int *)0x0;
LAB_0060e072:

    // Set various effect parameters (likely color/intensity values)
    // These are stored in global arrays at DAT_011f3a00+ offsets
    if (DAT_012058d0 < 0x19) {
        DAT_012058d0 = 0x19;
    }
    if (0x19 < DAT_00f15988) {
        DAT_00f15988 = 0x19;
    }
    _DAT_011f3a3c = 5; // +0x3c offset in effect data

    if (DAT_012058d0 < 0x18) {
        DAT_012058d0 = 0x18;
    }
    if (0x18 < DAT_00f15988) {
        DAT_00f15988 = 0x18;
    }
    _DAT_011f3a38 = 0; // +0x38 offset

    if (DAT_012058d0 < 0xf) {
        DAT_012058d0 = 0xf;
    }
    if (0xf < DAT_00f15988) {
        DAT_00f15988 = 0xf;
    }
    _DAT_011f3a14 = 0; // +0x14 offset

    if (DAT_012058d0 < 0x1b) {
        DAT_012058d0 = 0x1b;
    }
    if (0x1a < DAT_00f15988) {
        DAT_00f15988 = 0x1b;
    }
    _DAT_011f3a44 = 1; // +0x44 offset

    FUN_00417cf0(1, 2, 1); // set some effect flags

    if (DAT_012058d0 < 7) {
        DAT_012058d0 = 7;
    }
    if (7 < DAT_00f15988) {
        DAT_00f15988 = 7;
    }
    _DAT_011f39f4 = 0; // +0x? offset

    if (DAT_012058d0 < 0xe) {
        DAT_012058d0 = 0xe;
    }
    if (0xe < DAT_00f15988) {
        DAT_00f15988 = 0xe;
    }
    _DAT_011f3a10 = 0; // +0x10 offset

    if (DAT_012058d4 < 0xa8) {
        DAT_012058d4 = 0xa8;
    }
    if (0xa7 < DAT_00f1598c) {
        DAT_00f1598c = 0xa8;
    }
    _DAT_011f3c78 = 0xf; // +0x? offset

    if (DAT_012058d4 < 0xbe) {
        DAT_012058d4 = 0xbe;
    }
    if (0xbd < DAT_00f1598c) {
        DAT_00f1598c = 0xbe;
    }
    _DAT_011f3cd0 = 0xf; // +0x? offset

    if (DAT_012058d0 < 0x16) {
        DAT_012058d0 = 0x16;
    }
    if (0x16 < DAT_00f15988) {
        DAT_00f15988 = 0x16;
    }
    _DAT_011f3a30 = 1; // +0x30 offset

    // Set effect properties on the found effect object
    effectPtr[0x4e] = 6; // +0x138 offset
    effectPtr[5] = effectPtr[0x56]; // +0x14 and +0x158
    effectPtr[4] = effectPtr[0x6a]; // +0x10 and +0x1A8

    if (DAT_012058e8 == effectPtr) {
        FUN_0060a460(effectPtr[0x56]); // update effect
    }

    FUN_00611500(); // update effect state

    // Handle effect index validation and cleanup
    if ((effectIndex != 0xffffffff) && (effectIndex < 0x1000)) {
        iVar10 = effectIndex * 0x38;
        if ((&DAT_011a0f28 + iVar10 != (byte *)0x0) && ((byte)(&DAT_011a0f28)[iVar10] < 4)) {
            if (*(int *)(&DAT_011a0f44 + iVar10) != 0) {
                FUN_00606e60(*(int *)(&DAT_011a0f44 + iVar10), 0x3214000); // free memory
            }
            // Clear flags and set new ones
            *(uint *)(&DAT_011a0f34 + iVar10) = *(uint *)(&DAT_011a0f34 + iVar10) & 0xffadffff | 0x210000;
            FUN_006189c0(); // update effect state
        }
    }

    effectPtr[0x40] = effectIndex; // +0x100 offset - store effect index

    if ((DAT_012058e8 == effectPtr) && (effectPtr[0x3f] != 0)) {
        FUN_006063b0(); // update effect
    }

    // Call vtable method at offset +0x18 (likely update/render)
    (**(code **)(*effectPtr + 0x18))();

    // Allocate and setup a data structure (0xD type, size 4)
    puVar11 = (undefined4 *)FUN_0060cd00(0xd, 4, 0, 1, 0);
    uVar7 = DAT_00e2eff4;
    uVar5 = DAT_00e2b1a4;
    if (puVar11 != (undefined4 *)0x0) {
        *puVar11 = DAT_00e2eff4;
        puVar11[1] = uVar5;
        puVar11[2] = 0;
        puVar11[3] = 0;
        puVar11[4] = uVar5;
        puVar11[5] = uVar5;
        puVar11[6] = uVar5;
        puVar11[7] = 0;
        puVar11[8] = uVar5;
        puVar11[9] = uVar7;
        puVar11[10] = uVar5;
        puVar11[0xb] = uVar5;
        puVar11[0xc] = uVar7;
        puVar11[0xd] = uVar7;
        puVar11[0xe] = 0;
        puVar11[0xf] = uVar5;
        FUN_0060cde0(); // register data
    }

    // Call vtable method at offset +0x20 (likely finalize)
    (**(code **)(*effectPtr + 0x20))();

    // Validate target index and apply effect
    if (targetIndex < 0x1000) {
        effectData = &DAT_011a0f28 + targetIndex * 0x38;
    } else {
        effectData = (undefined1 *)0x0;
    }
    FUN_00606830(targetIndex, effectData); // apply effect to target

    // Set effect parameters again (second pass)
    if (DAT_012058d0 < 0x19) {
        DAT_012058d0 = 0x19;
    }
    if (0x19 < DAT_00f15988) {
        DAT_00f15988 = 0x19;
    }
    _DAT_011f3a3c = 7;

    if (DAT_012058d0 < 0x18) {
        DAT_012058d0 = 0x18;
    }
    if (0x18 < DAT_00f15988) {
        DAT_00f15988 = 0x18;
    }
    _DAT_011f3a38 = 0;

    if (DAT_012058d0 < 0xf) {
        DAT_012058d0 = 0xf;
    }
    if (0xf < DAT_00f15988) {
        DAT_00f15988 = 0xf;
    }
    _DAT_011f3a14 = 0;

    if (DAT_012058d0 < 7) {
        DAT_012058d0 = 7;
    }
    if (7 < DAT_00f15988) {
        DAT_00f15988 = 7;
    }
    _DAT_011f39f4 = 1;

    if (DAT_012058d0 < 0xe) {
        DAT_012058d0 = 0xe;
    }
    if (0xe < DAT_00f15988) {
        DAT_00f15988 = 0xe;
    }
    _DAT_011f3a10 = 1;

    if (DAT_012058d0 < 0x1b) {
        DAT_012058d0 = 0x1b;
    }
    if (0x1a < DAT_00f15988) {
        DAT_00f15988 = 0x1b;
    }
    _DAT_011f3a44 = 0;

    FUN_00417cf0(1, 5, 6); // set effect flags

    uVar5 = DAT_011f38f4;
    uVar8 = DAT_011f38f0;

    if (DAT_012058d0 < 0x16) {
        DAT_012058d0 = 0x16;
    }
    if (0x16 < DAT_00f15988) {
        DAT_00f15988 = 0x16;
    }
    _DAT_011f3a30 = 1;

    // Restore previous camera state
    DAT_011f38f0 = uVar6;
    DAT_011f38f4 = uVar9;
    FUN_00609340(0, uVar8, uVar5); // restore camera

    uVar6 = DAT_00e2b1a4;
    iVar10 = DAT_012058b0 * 0x18;
    *(undefined4 *)(&DAT_011f3918 + iVar10) = uVar1;
    *(undefined4 *)(&DAT_011f391c + iVar10) = uVar2;
    *(undefined4 *)(&DAT_011f3920 + iVar10) = uVar3;
    *(undefined4 *)(&DAT_011f3924 + iVar10) = uVar4;
    *(undefined4 *)(&DAT_011f3928 + iVar10) = 0;
    *(undefined4 *)(&DAT_011f392c + iVar10) = uVar6;
    FUN_00609500(uVar4, 0x3f800000); // finalize camera

    return;
}