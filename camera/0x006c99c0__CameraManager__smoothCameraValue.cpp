// FUNC_NAME: CameraManager::smoothCameraValue
void __thiscall CameraManager::smoothCameraValue(int this, float *param_2, float *param_3, float param_4, float param_5, float param_6)
{
    char cVar1;
    float10 fVar2;
    float fVar3;
    
    if ((float)((uint)param_4 & DAT_00e44680) <= DAT_00d5efd0) {
        fVar3 = 0.0;
        *(undefined4 *)(this + 0x74) = 0; // +0x74: accumulatedTime
    }
    else {
        param_5 = *(float *)(this + 0x74) + param_5; // +0x74: accumulatedTime
        *(float *)(this + 0x74) = param_5;
        if (param_2[4] < param_5) {
            *(float *)(this + 0x74) = param_2[4]; // clamp to max duration
        }
        fVar3 = *(float *)(this + 0x74) / param_2[4]; // normalized progress
    }
    cVar1 = FUN_00410eb0(); // likely isPaused() or similar
    if (cVar1 == '\0') {
        param_4 = ((param_2[1] - *param_2) * fVar3 + *param_2) * _DAT_00e50fb8 * DAT_00e445c8 * param_4;
        fVar3 = *param_3;
        if (DAT_0112a7a5 == '\0') {
            param_4 = DAT_00e44564 - param_4; // invert for non-inverted mode
        }
        fVar2 = (float10)FUN_004a1580(param_4 - fVar3); // likely lerp or smoothstep
        fVar2 = (float10)FUN_004a1580((float)(fVar2 * (float10)param_2[8] *
                                              (float10)*(float *)(this + 0x60) * (float10)param_6 +
                                             (float10)fVar3));
        *param_3 = (float)fVar2;
        return;
    }
    param_6 = param_2[1] * DAT_00e445c8 * param_4 * param_6;
    if (DAT_0112a7a5 == '\0') {
        *param_3 = DAT_00e44564 - param_6;
        return;
    }
    *param_3 = param_6;
    return;
}