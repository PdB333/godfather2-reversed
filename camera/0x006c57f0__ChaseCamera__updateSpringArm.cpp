// FUNC_NAME: ChaseCamera::updateSpringArm
void __thiscall ChaseCamera::updateSpringArm(int this, float *targetPos, float *cameraPos, undefined4 *quat, float *outPos, undefined4 param_6, float deltaTime)
{
    float fVar1;
    undefined4 *puVar2;
    float10 fVar3;
    float fVar4;
    float local_24;
    float local_20;
    float local_1c;
    float local_18;
    float local_14;
    float local_10;
    undefined1 local_c[4];
    float local_8;

    puVar2 = quat;
    // Decompose quaternion into forward vector
    FUN_004a2540(&local_18, *quat, quat[1]); // +0x00, +0x04

    // Calculate distance from camera to target
    fVar4 = DAT_00e44564 - *cameraPos; // Some global time or distance value

    // Interpolate camera position along forward vector
    local_24 = local_18 * fVar4 + *targetPos;
    local_20 = local_14 * fVar4 + targetPos[1];
    local_1c = local_10 * fVar4 + targetPos[2];

    // Check collision along spring arm
    fVar3 = (float10)FUN_006c9b00(&local_24, targetPos, local_c, 1); // Raycast function
    quat = (undefined4 *)(float)fVar3;
    if (fVar3 < (float10)0) {
        quat = (undefined4 *)0x0;
        fVar3 = (float10)0.0;
    }
    cameraPos = (float *)0x0;
    if (((float)quat < _DAT_00d5780c) && (DAT_00d5ef54 < local_8)) {
        cameraPos = (float *)0x1; // Collision detected flag
    }

    // Update spring arm length with smoothing
    fVar4 = *(float *)(this + 0x2d4); // Current spring arm length
    if (fVar4 <= (float)quat) {
        fVar1 = _DAT_00d5ef4c; // Spring arm extension speed
        if (DAT_00d5842c < fVar4) {
            fVar1 = DAT_00d5ef50; // Different speed for longer arms
        }
        quat = (undefined4 *)(*(float *)(this + 0x168) * fVar1); // Max speed * multiplier
        fVar3 = (float10)FUN_006c89b0(fVar4, (float)fVar3, quat); // Smooth interpolation
        *(float *)(this + 0x2d4) = (float)fVar3;
    } else {
        *(undefined4 **)(this + 0x2d4) = quat; // Direct set if shorter
    }

    // Apply spring arm to camera position
    FUN_006c45a0(&local_24, targetPos, puVar2, *(undefined4 *)(this + 0x2d4), cameraPos, targetPos, puVar2, &quat);

    // Lerp output position with deltaTime
    *outPos = (float)quat * DAT_00e445c8 * deltaTime + (_DAT_00d5780c - deltaTime) * *outPos;
    return;
}