// FUNC_NAME: someClass::updateThrottleOrBrake

void __fastcall someClass::updateThrottleOrBrake(int this)
{
    float fVar1;
    int iVar2;
    float fVar3;
    float fVar4;
    float fVar5;

    iVar2 = **(int **)(DAT_012233a0 + 4);
    fVar4 = *(float *)(this + 0x54); // +0x54: some input value
    fVar1 = *(float *)(this + 0x58); // +0x58: another input value
    fVar3 = fVar4;
    if (((iVar2 != 0) && (iVar2 != 0x1f30)) &&
        (fVar3 = (fVar4 + fVar1) * _DAT_00d5c458, fVar3 = fVar3 - (fVar1 - fVar3), fVar3 < 0.0)) {
        fVar3 = 0.0;
    }
    if (0.0 < fVar3 + _DAT_00d5780c) {
        fVar3 = fVar4;
        if (((iVar2 != 0) && (iVar2 != 0x1f30)) &&
            (fVar3 = (fVar4 + fVar1) * _DAT_00d5c458, fVar3 = fVar3 - (fVar1 - fVar3), fVar3 < 0.0)) {
            fVar3 = 0.0;
        }
        fVar5 = DAT_00d5e288;
        if (fVar3 + _DAT_00d5780c < DAT_00d5e288) {
            if (((iVar2 != 0) && (iVar2 != 0x1f30)) &&
                (fVar4 = (fVar4 + fVar1) * _DAT_00d5c458, fVar4 = fVar4 - (fVar1 - fVar4), fVar4 < 0.0)) {
                fVar4 = 0.0;
            }
            fVar5 = fVar4 + _DAT_00d5780c;
        }
    } else {
        fVar5 = 0.0;
    }
    fVar5 = fVar5 - *(float *)(this + 0x40); // +0x40: current value
    *(float *)(this + 0x40) = *(float *)(this + 0x40) + fVar5; // +0x40: update current value
    *(float *)(this + 0x4c) = fVar5 + *(float *)(this + 0x4c); // +0x4c: accumulate delta
    return;
}