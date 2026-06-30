// FUNC_NAME: ChaseCamera::updateCameraOrientation
void __thiscall ChaseCamera::updateCameraOrientation(int this, float *outLookAt, float *outUp, float *outPosition, undefined4 param5, float *outForward, float *outRight, float *outUpVec, float *outDistance)
{
    float fVar1;
    int iVar2;
    float10 fVar3;
    float fVar4;
    float fVar5;
    float local_20;
    float fStack_1c;
    float local_18;
    undefined4 local_14;

    // Get target entity pointer (offset +0xC0) and subtract 0x48 to get base
    if (*(int *)(this + 0xc0) == 0) {
        iVar2 = 0;
    } else {
        iVar2 = *(int *)(this + 0xc0) + -0x48;
    }
    FUN_006cc800(iVar2, outLookAt, 1); // Get look-at target position

    // Get up target entity pointer (offset +0xC8 = 200) and subtract 0x48 to get base
    if (*(int *)(this + 200) == 0) {
        iVar2 = 0;
    } else {
        iVar2 = *(int *)(this + 200) + -0x48;
    }
    FUN_006cc800(iVar2, outUp, 0); // Get up target position

    // Interpolate camera position between current and desired using global interpolation factor
    fVar4 = (*(float *)(this + 0xf0) - *(float *)(this + 0xe4)) * _DAT_00d5c458;
    fVar5 = (*(float *)(this + 0xf4) - *(float *)(this + 0xe8)) * _DAT_00d5c458;
    *outPosition = *(float *)(this + 0xe0) +
                   (*(float *)(this + 0xec) - *(float *)(this + 0xe0)) * _DAT_00d5c458;
    outPosition[1] = *(float *)(this + 0xe4) + fVar4;
    outPosition[2] = *(float *)(this + 0xe8) + fVar5;

    FUN_006cd650(param5); // Some initialization/reset function

    // Compute forward vector from lookAt to up
    fVar4 = outUp[2];
    fVar5 = outLookAt[2];
    *(ulonglong *)outForward = CONCAT44(outUp[1] - outLookAt[1], *outUp - *outLookAt);
    outForward[2] = fVar4 - fVar5;

    local_20 = *outForward;
    fStack_1c = outForward[1];
    local_18 = outForward[2];
    local_14 = 0;
    fVar3 = (float10)FUN_0056afa0(&local_20, &local_20); // Vector length calculation
    *outForward = local_20;
    outForward[1] = fStack_1c;
    outForward[2] = local_18;

    FUN_006cc6c0(outLookAt, outUp, 0, outUpVec); // Compute up vector from lookAt and up

    fVar1 = DAT_00e44598; // Some threshold constant
    // Compute right vector as cross product of forward and up
    *outRight = outUpVec[2] * outForward[1] - outForward[2] * outUpVec[1];
    outRight[1] = outForward[2] * *outUpVec - *outForward * outUpVec[2];
    outRight[2] = *outForward * outUpVec[1] - *outUpVec * outForward[1];

    fVar5 = DAT_00d5ccf8;
    fVar4 = _DAT_00d5780c;
    if ((float)fVar3 <= fVar1) {
        // If forward vector is too short (near zero), use default orientation
        *outRight = 0.0;
        outRight[1] = fVar4;
        outRight[2] = 0.0;
        *outUpVec = 0.0;
        outUpVec[1] = 0.0;
        outUpVec[2] = fVar5;
        *outForward = fVar4;
        outForward[1] = 0.0;
        outForward[2] = 0.0;
    }

    // Compute distance from camera position to target along up vector
    *outDistance = *outUpVec * (*(float *)(this + 0x20) - *outPosition) +
                   (*(float *)(this + 0x24) - outPosition[1]) * outUpVec[1] +
                   outUpVec[2] * (*(float *)(this + 0x28) - outPosition[2]);
    return;
}