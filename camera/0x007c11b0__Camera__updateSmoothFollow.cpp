// FUNC_NAME: Camera::updateSmoothFollow
void __thiscall Camera::updateSmoothFollow(int thisPtr, undefined4 param_2, float deltaTime, undefined4 param_4, undefined4 param_5, undefined4 param_6)
{
    bool bActive;
    float fVar2;
    float fVar3;
    char cActive;
    float fVar5;
    float fVar6;
    float fVar7;
    float fVar8;
    float inputX;
    float inputY;

    cActive = isActive(); // FUN_00410eb0 - checks if camera is active
    if (cActive == '\0') {
        fVar7 = 0.0;
        // Reset all motion state
        *(undefined4 *)(thisPtr + 0xa4) = 0; // +0xa4: positionX
        *(undefined4 *)(thisPtr + 0xa8) = 0; // +0xa8: positionY
        *(undefined4 *)(thisPtr + 0xac) = 0; // +0xac: velocityX
        *(undefined4 *)(thisPtr + 0xb0) = 0; // +0xb0: velocityY
        *(undefined4 *)(thisPtr + 0xb4) = 0; // +0xb4: timeAccumulator
        *(undefined4 *)(thisPtr + 0xb8) = 0; // +0xb8: extraAccumulator
    }
    else {
        // Get input axis (controller 1, deadzone constants)
        getInputAxis(1, &inputX, &inputY, 0, 0, DAT_00d5ccf8, DAT_00d5ccf8, DAT_00d5ccf8); // FUN_0079eab0
        fVar3 = DAT_00d5f374; // maxTimeStep?
        fVar7 = deltaTime + *(float *)(thisPtr + 0xb4); // accumulate time
        bActive = fVar7 < DAT_00d5f374;
        inputX = inputX + *(float *)(thisPtr + 0xac); // add velocity to input
        inputY = inputY + *(float *)(thisPtr + 0xb0);
        *(float *)(thisPtr + 0xb4) = fVar7; // store accumulated time
        *(float *)(thisPtr + 0xac) = inputX; // store velocityX
        *(float *)(thisPtr + 0xb0) = inputY; // store velocityY
        fVar8 = DAT_00d5ccf8; // zero constant
        fVar2 = _DAT_00d5780c; // maxPosition?
        if (bActive) goto LAB_007c138e;
        // Apply damping and clamp
        inputY = inputY * DAT_00d5842c; // damping factor
        fVar5 = *(float *)(thisPtr + 0xa4) + inputX * DAT_00d5842c; // damped positionX
        *(undefined4 *)(thisPtr + 0xac) = 0; // reset velocityX
        *(undefined4 *)(thisPtr + 0xb0) = 0; // reset velocityY
        fVar6 = fVar8; // zero
        if ((fVar8 <= fVar5) && (fVar6 = fVar5, fVar2 < fVar5)) {
            fVar6 = fVar2; // clamp to max
        }
        fVar5 = *(float *)(thisPtr + 0xa8) + inputY; // damped positionY
        *(float *)(thisPtr + 0xa4) = fVar6; // store clamped positionX
        fVar6 = DAT_00d6bfd8; // threshold for something
        if ((fVar8 <= fVar5) && (fVar8 = fVar5, fVar2 < fVar5)) {
            fVar8 = fVar2; // clamp positionY
        }
        inputY = (fVar3 / fVar7) * inputY; // scale by time ratio
        inputY = inputY * inputY; // square
        *(float *)(thisPtr + 0xa8) = fVar8; // store clamped positionY
        if ((fVar6 <= inputY) || (DAT_00d5f378 <= fVar8)) {
            *(undefined4 *)(thisPtr + 0xb8) = 0; // reset extra accumulator
        }
        else {
            *(float *)(thisPtr + 0xb8) = fVar7 + *(float *)(thisPtr + 0xb8); // accumulate extra
        }
        if ((inputY <= fVar6) || (DAT_00e44828 < fVar8)) {
            fVar7 = *(float *)(thisPtr + 0xbc) - fVar7; // +0xbc: targetPosition?
            if (fVar7 < 0.0) {
                fVar7 = 0.0;
            }
            *(undefined4 *)(thisPtr + 0xb4) = 0; // reset time accumulator
        }
        else {
            fVar7 = *(float *)(thisPtr + 0xbc) + fVar7;
            *(undefined4 *)(thisPtr + 0xb4) = 0;
        }
    }
    *(float *)(thisPtr + 0xbc) = fVar7; // store updated target
LAB_007c138e:
    baseUpdate(param_2, deltaTime, param_4, param_5, param_6); // FUN_004aba80 - likely base class update
    return;
}