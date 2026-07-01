// FUNC_NAME: PlayerVehicleComponent::updateThrottleAndBrake
void __fastcall PlayerVehicleComponent::updateThrottleAndBrake(int this)
{
    uint uVar1;
    int extraout_ECX;
    int extraout_ECX_00;
    int extraout_ECX_01;
    int extraout_ECX_02;
    int extraout_EDX;
    int extraout_EDX_00;
    int extraout_EDX_01;
    int iVar2;
    float10 fVar3;
    float10 fVar4;
    float10 fVar5;
    float10 fVar6;
    float10 extraout_ST1;
    float10 extraout_ST1_00;
    float10 extraout_ST1_01;
    float fVar7;
    float fVar8;
    float fVar9;
    float local_4;

    fVar8 = _DAT_00d5780c; // Some global float (max throttle/brake?)
    fVar6 = (float10)1;
    fVar3 = (float10)DAT_00d5efb8; // Some global float (acceleration factor?)
    fVar5 = (float10)0;
    fVar9 = 0.0;
    iVar2 = DAT_01206804; // Some global int (delta time?)
    if (*(int *)(this + 0x6c4) == 0) goto LAB_007faf7d; // +0x6c4: throttleTimer
    uVar1 = *(int *)(this + 0x6c4) + DAT_01206804;
    *(uint *)(this + 0x6c4) = uVar1;
    if (999 < uVar1) {
        if ((*(byte *)(this + 0x6dc) & 8) == 0) { // +0x6dc: flags (bit 3 = brake?)
            fVar6 = (float10)FUN_007f49e0((float)fVar6,1,0); // Apply throttle
            this = extraout_ECX_01;
            iVar2 = extraout_EDX_01;
            fVar3 = extraout_ST1_01;
        }
        else {
            fVar5 = (float10)FUN_007f49e0((float)fVar5,1,0); // Apply brake
            this = extraout_ECX_00;
            iVar2 = extraout_EDX_00;
            fVar3 = extraout_ST1_00;
        }
        *(undefined4 *)(this + 0x6c4) = 0; // Reset throttleTimer
        goto LAB_007faf7d;
    }
    fVar4 = (float10)(int)(1000 - uVar1);
    if ((int)(1000 - uVar1) < 0) {
        fVar4 = fVar4 + (float10)DAT_00e44578; // Some global float (overflow correction?)
    }
    local_4 = (float)(fVar4 * fVar3);
    if (fVar5 < fVar4 * fVar3) {
        fVar7 = fVar8;
        if (fVar8 <= local_4) goto LAB_007faf23;
    }
    else {
        fVar7 = 0.0;
LAB_007faf23:
        local_4 = fVar7;
    }
    if ((*(byte *)(this + 0x6dc) & 8) == 0) { // +0x6dc: flags (bit 3 = brake?)
        local_4 = fVar8 - local_4; // Invert for throttle (0 = full, max = none)
    }
    fVar5 = (float10)FUN_007f49e0(local_4,1,0); // Apply throttle/brake
    this = extraout_ECX;
    iVar2 = extraout_EDX;
    fVar3 = extraout_ST1;
LAB_007faf7d:
    if (*(int *)(this + 0x6c0) == 0) { // +0x6c0: brakeTimer
        return;
    }
    uVar1 = *(int *)(this + 0x6c0) + iVar2;
    *(uint *)(this + 0x6c0) = uVar1;
    if (999 < uVar1) {
        if ((*(byte *)(this + 0x6dc) & 4) != 0) { // +0x6dc: flags (bit 2 = handbrake?)
            fVar6 = fVar5;
        }
        FUN_007f49e0((float)fVar6,0,1); // Apply handbrake
        *(undefined4 *)(extraout_ECX_02 + 0x6c0) = 0; // Reset brakeTimer
        return;
    }
    fVar6 = (float10)(int)(1000 - uVar1);
    if ((int)(1000 - uVar1) < 0) {
        fVar6 = fVar6 + (float10)DAT_00e44578;
    }
    fVar7 = (float)(fVar6 * fVar3);
    if ((*(byte *)(this + 0x6dc) & 4) == 0) { // +0x6dc: flags (bit 2 = handbrake?)
        fVar7 = fVar8 - fVar7; // Invert for brake
    }
    local_4 = fVar9;
    if ((fVar9 < fVar7) && (local_4 = fVar7, fVar8 <= fVar7)) {
        local_4 = fVar8;
    }
    FUN_007f49e0(local_4,0,1); // Apply brake
    return;
}