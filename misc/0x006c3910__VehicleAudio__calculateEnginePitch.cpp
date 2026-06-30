// FUNC_NAME: VehicleAudio::calculateEnginePitch
float __thiscall VehicleAudio::calculateEnginePitch(int this, undefined4 param_2, undefined4 param_3, float param_4)
{
    float fVar1;
    float10 fVar2;
    float10 fVar3;
    float10 fVar4;
    float10 fVar5;
    undefined4 local_8;
    undefined4 local_4;
    
    if (*(char *)(this + 700) == '\0') {
        local_4 = *(float *)(this + 0x104); // +0x104: basePitch
    }
    else {
        fVar1 = *(float *)(this + 0x2dc); // +0x2dc: currentRPM
        if (_DAT_00d5780c < fVar1) {
            local_4 = (*(float *)(this + 0x1d0) - *(float *)(this + 0x104)) *
                      (fVar1 - _DAT_00d5780c) + *(float *)(this + 0x104);
        }
        else {
            local_4 = (*(float *)(this + 0x104) - *(float *)(this + 0x1c0)) * fVar1 +
                      *(float *)(this + 0x1c0);
        }
    }
    if (*(char *)(this + 700) == '\0') {
        local_8 = *(float *)(this + 0x108); // +0x108: basePitch2
    }
    else {
        fVar1 = *(float *)(this + 0x2dc);
        if (_DAT_00d5780c < fVar1) {
            local_8 = (*(float *)(this + 0x1d4) - *(float *)(this + 0x108)) *
                      (fVar1 - _DAT_00d5780c) + *(float *)(this + 0x108);
        }
        else {
            local_8 = (*(float *)(this + 0x108) - *(float *)(this + 0x1c4)) * fVar1 +
                      *(float *)(this + 0x1c4);
        }
    }
    fVar2 = (float10)FUN_006c89b0(local_4, local_8, param_2); // calculatePitchFromRPM
    if (*(char *)(this + 700) != '\0') {
        fVar3 = (float10)FUN_006c36e0(local_4, local_8); // calculatePitchModifier
        fVar4 = (float10)FUN_006c37f0(); // getMinPitch
        fVar5 = (float10)FUN_006c91c0(param_3, _DAT_00e50e70, _DAT_00e50e74, _DAT_0112a784, _DAT_00e50f7c); // calculateLoadFactor
        fVar2 = (fVar5 * (float10)param_4 + (float10)_DAT_00d5780c) *
                (float10)(float)(fVar3 + (float10)(float)fVar2);
        if (fVar2 <= (float10)(float)fVar4) {
            fVar2 = (float10)(float)fVar4;
        }
    }
    return fVar2;
}