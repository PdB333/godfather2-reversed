// FUNC_NAME: AnimationBlend::blendTwoAnimations
uint32_t AnimationBlend::blendTwoAnimations(uint32_t param_1, float param_2, int *param_3, float param_4, uint32_t param_5, uint32_t param_6, uint32_t param_7)
{
    byte bVar1;
    short sVar2;
    byte *pbVar3;
    byte *pbVar4;
    int *piVar5;
    uint uVar6;
    uint32_t uVar7;
    float fVar8;
    
    piVar5 = param_3;
    if (*(char *)((int)param_2 + 1) > 1) { // Check if animation has more than 1 frame
        pbVar3 = *(byte **)((int)param_2 + 0xc); // +0xC: animation data pointer 1
        pbVar4 = *(byte **)((int)param_2 + 0x10); // +0x10: animation data pointer 2
        sVar2 = *(short *)(pbVar4 + 2); // +2: frame count for second animation
        if ((uint)param_3[1] <= (uint)(int)sVar2) {
            param_2 = 0.0f;
            FUN_00591c00(&param_2); // likely clamp or normalize function
        }
        uVar6 = param_6;
        fVar8 = *(float *)(*piVar5 + sVar2 * 4); // Get blend weight from array
        if (fVar8 == DAT_00e2b1a4) { // DAT_00e2b1a4 = 1.0f (identity weight)
            param_2 = param_4 - (float)(int)param_4; // fractional part of param_4
        }
        else {
            fVar8 = fVar8 - DAT_00e2b1a4;
            param_2 = param_4;
            if (fVar8 < param_4) {
                param_2 = param_4 - (float)(int)(param_4 / fVar8) * fVar8; // modulo operation
            }
        }
        bVar1 = *pbVar3;
        if ((bVar1 & 0x3f) < 0x23) { // 0x23 = 35, animation opcode limit
            (*(code **)(&DAT_0103afc0 + (bVar1 & 0x3f) * 4)) // dispatch table for animation ops
                (param_1, pbVar3, piVar5, param_4, param_5, param_6, param_7);
        }
        if ((*pbVar4 & 0x3f) < 0x23) {
            uVar7 = (*(code **)(&DAT_0103afc0 + (*pbVar4 & 0x3f) * 4))
                        (param_1, pbVar4, piVar5, param_2, param_5, uVar6 | 0x80, param_7);
        }
        else {
            uVar7 = 0;
        }
        uVar7 = FUN_00583460(uVar7); // post-process animation result
        FUN_0056fb60(); // cleanup function (called twice)
        FUN_0056fb60();
        return uVar7;
    }
    return 0;
}