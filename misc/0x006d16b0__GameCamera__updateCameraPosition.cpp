// FUNC_NAME: GameCamera::updateCameraPosition
void __thiscall GameCamera::updateCameraPosition(int this, undefined4 param_2, float *targetPos, undefined4 *targetRot, float deltaTime, char isForced) 
{
    char cVar1;
    float lerpFactor;
    float fVar3;
    float fVar4;
    float fVar5;
    float fVar6;
    float fVar7;
    float fVar8;
    float fVar9;
    float fVar10;
    float fVar11;
    float fVar12;
    float fVar13;
    float fVar14;

    // Check if forced update or if some global condition allows smooth interpolation
    if ((isForced == '\0') && (cVar1 = FUN_00410eb0(), cVar1 == '\0')) {
        // Smooth interpolation with separate Y axis factor (likely for vertical axis scaling)
        lerpFactor = *(float *)(this + 0x8c);  // +0x8c: interpolation factor (lerp alpha)
        fVar8 = (*targetPos - *(float *)(this + 0x10)) * lerpFactor + *(float *)(this + 0x10);  // +0x10: current position X
        fVar9 = (targetPos[1] - *(float *)(this + 0x14)) * lerpFactor * _DAT_00e51138 + *(float *)(this + 0x14);  // +0x14: current position Y (with extra Y scaling)
        fVar10 = (targetPos[2] - *(float *)(this + 0x18)) * lerpFactor + *(float *)(this + 0x18);  // +0x18: current position Z
        fVar3 = _DAT_00d5780c;  // Global time delta or 1.0f?
    }
    else {
        // Direct assignment (no interpolation)
        lerpFactor = *(float *)(this + 0x8c);
        fVar8 = (*targetPos - *(float *)(this + 0x10)) * lerpFactor + *(float *)(this + 0x10);
        fVar9 = (targetPos[1] - *(float *)(this + 0x14)) * lerpFactor + *(float *)(this + 0x14);
        fVar10 = (targetPos[2] - *(float *)(this + 0x18)) * lerpFactor + *(float *)(this + 0x18);
        fVar3 = (targetPos[3] - *(float *)(this + 0x1c)) * lerpFactor + *(float *)(this + 0x1c);  // +0x1c: current w component (quaternion or extra)
    }

    // Compute delta from current position
    fVar8 = fVar8 - *(float *)(this + 0x10);
    fVar9 = fVar9 - *(float *)(this + 0x14);
    fVar10 = fVar10 - *(float *)(this + 0x18);
    fVar3 = fVar3 - *(float *)(this + 0x1c);

    // Compute velocity components (position delta * some factor / deltaTime)
    fVar2 = _DAT_00d5780c / deltaTime;  // 1.0f / deltaTime effectively
    fVar4 = fVar2 * fVar8;
    fVar5 = fVar2 * fVar9;
    fVar6 = fVar2 * fVar10;
    fVar7 = fVar2 * fVar3;

    // Compute acceleration-like damped velocity (difference from current velocity)
    fVar11 = (fVar4 - *(float *)(this + 0x40)) * fVar2;  // +0x40: current velocity X
    fVar12 = (fVar5 - *(float *)(this + 0x44)) * fVar2;  // +0x44: current velocity Y
    fVar13 = (fVar6 - *(float *)(this + 0x48)) * fVar2;  // +0x48: current velocity Z
    fVar14 = SQRT(fVar12 * fVar12 + fVar11 * fVar11 + fVar13 * fVar13);  // Acceleration magnitude

    // Clamp velocity if acceleration exceeds maximum (max acceleration stored at +0x90)
    if ((isForced == '\0') && (*(float *)(this + 0x90) < fVar14)) {  // +0x90: max acceleration
        float clampFactor = *(float *)(this + 0x90) / fVar14;
        fVar4 = clampFactor * fVar11 * deltaTime + *(float *)(this + 0x40);
        fVar5 = clampFactor * fVar12 * deltaTime + *(float *)(this + 0x44);
        fVar6 = clampFactor * fVar13 * deltaTime + *(float *)(this + 0x48);
        fVar7 = clampFactor * (fVar7 - *(float *)(this + 0x4c)) * fVar2 * deltaTime + *(float *)(this + 0x4c);  // +0x4c: current velocity w
        // Recompute position deltas with clamped velocity
        fVar8 = deltaTime * fVar4;
        fVar9 = deltaTime * fVar5;
        fVar10 = deltaTime * fVar6;
        fVar3 = deltaTime * fVar7;
    }
    // else: position deltas already computed above

    // Update position
    *(float *)(this + 0x10) = *(float *)(this + 0x10) + fVar8;
    *(float *)(this + 0x14) = *(float *)(this + 0x14) + fVar9;
    *(float *)(this + 0x18) = *(float *)(this + 0x18) + fVar10;
    *(float *)(this + 0x1c) = *(float *)(this + 0x1c) + fVar3;

    // Update velocity
    *(float *)(this + 0x40) = fVar4;
    *(float *)(this + 0x44) = fVar5;
    *(float *)(this + 0x48) = fVar6;
    *(float *)(this + 0x4c) = fVar7;

    // Update rotation (quaternion) with interpolation
    float blendRatio = DAT_00e51160;  // Default blend ratio
    cVar1 = FUN_00410eb0();  // Check some game state (e.g., is cinematic/cutscene active?)
    fVar3 = _DAT_00d5780c;
    if (cVar1 != '\0') {
        blendRatio = DAT_00e511a0;  // Different blend ratio when in special state
    }

    *(undefined4 *)(this + 0x20) = *targetRot;   // +0x20: rotation X or w
    *(float *)(this + 0x24) = (fVar3 - blendRatio) * *(float *)(this + 0x24) + (float)targetRot[1] * blendRatio;  // +0x24: rotation Y (interpolated)
    *(undefined4 *)(this + 0x28) = targetRot[2]; // +0x28: rotation Z
    *(float *)(this + 0x2c) = fVar3;             // +0x2c: rotation w (set to 1.0f or time delta)
}