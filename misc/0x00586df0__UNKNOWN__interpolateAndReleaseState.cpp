// FUNC_NAME: UNKNOWN::interpolateAndReleaseState
int __thiscall UNKNOWN::interpolateAndReleaseState(int param_1, int param_2, uint param_3)
{
    bool bVar1;
    char cVar2;
    int in_EAX;
    undefined4 uVar3;
    float fVar4;
    float fVar5;
    float local_40;
    float fStack_3c;
    float fStack_38;
    float fStack_34;
    float local_30;
    float fStack_2c;
    float fStack_28;
    float fStack_24;
    undefined1 local_20 [28];

    fVar5 = DAT_00e2b1a4;
    fStack_38 = 0.0;
    fStack_3c = 0.0;
    local_40 = 0.0;
    fStack_34 = DAT_00e2b1a4;
    fStack_28 = 0.0;
    fStack_2c = 0.0;
    local_30 = 0.0;
    fStack_24 = DAT_00e2b1a4;
    // Check if any of bits 9, 10, or 11 of param_3 are set
    if ((param_3 & 0xe00) == 0) {
        bVar1 = false;
    }
    else {
        if ((param_3 >> 9 & 1) != 0) {
            // +0x10: x position
            local_30 = *(float *)(param_1 + 0x10);
        }
        if ((param_3 >> 10 & 1) != 0) {
            // +0x14: y position
            fStack_2c = *(float *)(param_1 + 0x14);
        }
        if ((param_3 >> 0xb & 1) != 0) {
            // +0x18: z position
            fStack_28 = *(float *)(param_1 + 0x18);
        }
        bVar1 = true;
    }
    // Check if value at param_1+0x0c equals a sentinel float (likely NaN or special marker)
    if (*(float *)(param_1 + 0xc) == DAT_00e2b1a4) {
        if (bVar1) {
            fVar4 = *(float *)(in_EAX + 0x1c) - DAT_00e2b1a4;
            *(float *)(in_EAX + 0x10) = *(float *)(in_EAX + 0x10) - local_30;
            *(float *)(in_EAX + 0x14) = *(float *)(in_EAX + 0x14) - fStack_2c;
            *(float *)(in_EAX + 0x18) = *(float *)(in_EAX + 0x18) - fStack_28;
            *(float *)(in_EAX + 0x1c) = fVar4;
            *(float *)(in_EAX + 0x1c) = fVar5;
        }
    }
    else {
        cVar2 = FUN_005871e0(param_1, param_3);
        if (cVar2 == '\0') {
            if (bVar1) {
                *(float *)(in_EAX + 0x10) = *(float *)(in_EAX + 0x10) - local_30;
                *(float *)(in_EAX + 0x14) = *(float *)(in_EAX + 0x14) - fStack_2c;
                *(float *)(in_EAX + 0x18) = *(float *)(in_EAX + 0x18) - fStack_28;
                *(float *)(in_EAX + 0x1c) = *(float *)(in_EAX + 0x1c) - fStack_24;
                *(float *)(in_EAX + 0x1c) = DAT_00e2b1a4;
            }
        }
        else {
            uVar3 = FUN_0056cdc0();
            FUN_0056cba0(uVar3);
            if (bVar1) {
                local_40 = *(float *)(in_EAX + 0x10) - local_30;
                fStack_3c = *(float *)(in_EAX + 0x14) - fStack_2c;
                fStack_38 = *(float *)(in_EAX + 0x18) - fStack_28;
                fStack_34 = DAT_00e2b1a4;
                fVar5 = DAT_00e2b1a4;
                FUN_0056ce80(local_20, &local_40, in_EAX + 0x10);
                *(float *)(in_EAX + 0x1c) = fVar5;
            }
        }
    }
    FUN_005872d0(param_2, param_3);
    // Transfer values from source to destination and clear source
    if ((param_3 & 1) != 0) {
        // +0x10: x position
        *(undefined4 *)(param_2 + 0x10) = *(undefined4 *)(in_EAX + 0x10);
        *(undefined4 *)(in_EAX + 0x10) = 0;
    }
    if ((param_3 >> 1 & 1) != 0) {
        // +0x14: y position
        *(undefined4 *)(param_2 + 0x14) = *(undefined4 *)(in_EAX + 0x14);
        *(undefined4 *)(in_EAX + 0x14) = 0;
    }
    if ((param_3 >> 2 & 1) != 0) {
        // +0x18: z position
        *(undefined4 *)(param_2 + 0x18) = *(undefined4 *)(in_EAX + 0x18);
        *(undefined4 *)(in_EAX + 0x18) = 0;
    }
    return param_2;
}