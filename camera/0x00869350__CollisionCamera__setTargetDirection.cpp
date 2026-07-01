// FUNC_NAME: CollisionCamera::setTargetDirection

void __thiscall CollisionCamera::setTargetDirection(const float *targetDirection)
{
    float fVar1;
    char cVar2;
    float fVar3;
    float fVar4;
    double dVar5;
    float local_24;
    float local_20;
    float local_1c;
    float local_18;
    float local_10;
    // 12-byte buffer for transform data (probably a matrix or quaternion)
    char local_c[12];

    // Set the target direction immediately (maybe store or normalize)
    setDirection(targetDirection);

    // Get current transform/rotation data
    cVar2 = getTransform(local_c);

    // Apply some transformation (e.g., scale or orientation) based on the transform
    setTransformComponent(1, cVar2, -(uint)(cVar2 != '\0') & (uint)local_c);

    // Check if smoothing is active (field +0xf2c != 1)
    if (*(int *)(this + 0xf2c) != 1) {
        fVar4 = *(float *)(this + 0xfc4);            // current speed
        // current direction stored at +0x1050, +0x1054, +0x1058
        local_24 = *(float *)(this + 0x1050);
        local_20 = *(float *)(this + 0x1054);
        local_1c = *(float *)(this + 0x1058);
        fVar1 = *(float *)(this + 0x1148);           // rotation speed delta

        // Save copies for later math
        local_18 = local_24;
        local_10 = local_1c;

        // If current speed is non-zero, apply a rotation along the Y axis?
        if (fVar4 != _DAT_00d577a0) {                // probably 0.0f
            dVar5 = (double)fVar1;
            cosf();                                  // cosine of fVar1
            local_24 = local_18 - (float)dVar5 * fVar4;  // rotate X component
            dVar5 = (double)fVar1;
            sinf();                                  // sine of fVar1
            local_1c = (float)dVar5 * fVar4 + local_10;  // rotate Z component
        }

        // Decide whether to use target speed or randomize
        if ((*(int *)(this + 0xfd0) < 1) || (cVar2 = isPointValid(&local_24), cVar2 == '\0')) {
            // Use target speed (from +0xfc8)
            fVar4 = *(float *)(this + 0xfc8);
            *(float *)(this + 0xfc4) = fVar4;
        } else {
            // Randomize speed
            *(int *)(this + 0xfd0) = 0;
            fVar3 = (float)randomFloat(0, *(uint *)(this + 0xfd4) & 0x7fffffff,
                                           *(uint *)(this + 0xfd4) >> 0x1f);
            fVar4 = fVar3;
            *(float *)(this + 0xfc4) = fVar3;
            *(float *)(this + 0xfc8) = fVar3;
        }

        fVar1 = *(float *)(this + 0x1148);
        local_20 = targetDirection[1];

        if (fVar4 == _DAT_00d577a0) {
            // If speed is zero, use target direction directly
            local_24 = *targetDirection;
            local_1c = targetDirection[2];
        } else {
            // Interpolate towards target direction (with rotation)
            dVar5 = (double)fVar1;
            cosf();
            local_24 = *targetDirection - (float)dVar5 * fVar4;
            dVar5 = (double)fVar1;
            sinf();
            local_1c = (float)dVar5 * fVar4 + targetDirection[2];
        }

        // Store the smoothed direction
        setDirection(&local_24);

        // Clear a flag (bit 15) to indicate direction has been updated
        *(uint *)(this + 0xf28) = *(uint *)(this + 0xf28) & 0xffff7fff;
        return;
    }

    // If smoothing is disabled (field == 1), just set the target direction directly
    setDirection(targetDirection);
    return;
}