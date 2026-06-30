// FUNC_NAME: EffectManager::updateLensFlareParams
void __thiscall EffectManager::updateLensFlareParams(int this, int param_2)
{
    float fVar1;
    int extraout_EDX;
    double dVar2;
    float fVar3;
    float local_a0;
    float local_9c;
    float local_98;
    undefined4 local_94;
    float local_90;
    undefined4 uStack_8c;
    undefined4 uStack_88;
    undefined4 uStack_84;
    undefined4 local_80;
    float fStack_7c;
    undefined4 uStack_78;
    undefined4 uStack_74;
    undefined4 local_70;
    undefined4 uStack_6c;
    float fStack_68;
    undefined4 uStack_64;
    undefined4 local_60;
    undefined4 uStack_5c;
    float fStack_58;
    float fStack_54;

    if (*(char *)(this + 0xc) == '\0') { // +0x0C: active flag
        FUN_00419370();
        // After call, extraout_EDX is the EDX return value (likely a pointer to some manager)
        fVar3 = *(float *)(*(int *)(extraout_EDX + 8) + 0x70 + *(int *)(param_2 + 0x18)); // +0x18: index into a float table
        local_90 = DAT_00e2b1a4; // default scale
        uStack_8c = 0;
        uStack_88 = 0;
        uStack_84 = 0;
        local_80 = 0;
        fStack_7c = DAT_00e2b1a4;
        uStack_78 = 0;
        uStack_74 = 0;
        local_70 = 0;
        uStack_6c = 0;
        fStack_68 = DAT_00e2b1a4;
        uStack_64 = 0;
        local_60 = 0;
        uStack_5c = 0;
        fStack_58 = 0.0;
        fStack_54 = DAT_00e2b1a4;
        // Another table read at offset 0x6c using same index
        fVar1 = *(float *)(*(int *)(extraout_EDX + 8) + *(int *)(param_2 + 0x18) + 0x6c);
        if (fVar1 <= DAT_00e2a850) {
            dVar2 = (double)fVar1;
            FUN_00b99fcb(); // some math function (likely sin/cos or random)
            local_90 = (float)dVar2 * fVar3;
            fStack_58 = 0.0;
        }
        else {
            dVar2 = (double)(fVar1 - DAT_00e2a850);
            FUN_00b99fcb();
            fStack_58 = (float)dVar2 * fVar3;
            local_90 = fVar3;
            fVar3 = fStack_58 + fVar3;
        }
        fStack_58 = DAT_00e44564 - fStack_58;
        fStack_7c = local_90;
        fStack_68 = fVar3;
        FUN_00417560(); // another processing step
        local_a0 = DAT_00e2b1a4 / local_90;
        local_98 = DAT_00e2b1a4 / fStack_68;
        local_9c = DAT_00e2b1a4 / fStack_7c;
        local_94 = 0;
        // Call to set global flare parameters with the three computed scales
        FUN_0056b0e0(&DAT_01163610, &DAT_011629d0, &local_a0);
    }
    return;
}