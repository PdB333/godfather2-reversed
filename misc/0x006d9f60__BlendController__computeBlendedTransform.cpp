// FUNC_NAME: BlendController::computeBlendedTransform
void __thiscall BlendController::computeBlendedTransform(int thisPtr, float deltaTime, int unusedParam, float* outTransform)
{
    // thisPtr is a struct: offset definitions:
    // +0x00: vtable? (not used)
    // +0x08: byte flag (set to 1 on completion)
    // +0x20: max speed factor (used for velocity calculation)
    // +0x24: speed decrement per frame
    // +0x28: some transform component (vector? used in interpolation)
    // +0x2C: duration (time until blend ends)
    // +0x30: another transform component (x)
    // +0x34: y
    // +0x38: z
    // +0x40: blend type (compared to global constant)
    // +0x50: current blend progress (scalar, decreases over time)
    // +0x54: accumulated progress (0.0 to max)
    // +0x58: speed (computed from distance and max speed)
    // +0x60: start position x
    // +0x64: start position y
    // +0x68: start position z
    // +0x6C: start position w? (unused in result)
    // +0x70: target position x
    // +0x74: target position y
    // +0x78: target position z
    // +0x7C: target position w? (unused in result)

    float* progressPtr = (float*)(thisPtr + 0x54);
    float fStack_74 = 0.0f;
    float fStack_78 = 0.0f;
    float fStack_7c = 0.0f;
    float local_80 = 0.0f;
    float fStack_54 = 0.0f;
    float fStack_58 = 0.0f;
    float fStack_5c = 0.0f;
    float local_60 = 0.0f;

    // Global constants (likely from .data section)
    float maxProgress = _DAT_00d5780c;          // e.g., 1.0f
    float someScale = _DAT_00d5eee4;            // e.g., 0.5f
    float anotherZero = _DAT_00d5f5bc;          // 0.0f
    float* epsilonPtr = PTR_FUN_00e4462c;       // pointer to a small float (e.g., 0.0001f)

    float local_88 = maxProgress; // copy of max progress

    if (maxProgress <= *(float*)(thisPtr + 0x54)) {
        // Compute new target position using a pseudo-random pattern from global arrays
        // DAT_012054b4 is an index that increments by 4 each call
        // DAT_010c2678 is a mask (e.g., 0x7FFFFFFF)
        int index = DAT_012054b4;
        int mask = DAT_010c2678;
        int idx0 = mask & index;
        int idx1 = mask & (index + 1);
        int idx2 = mask & (index + 2);
        int idx3 = mask & (index + 3);

        // Global array of floats at DAT_010c2680 (size unknown, but accessed with idx*4)
        float* globalArray = (float*)&DAT_010c2680;
        float fVar7 = *(float*)(thisPtr + 0x28);
        float fVar6 = globalArray[idx3] * someScale - maxProgress;

        DAT_012054b4 = index + 4;

        // Interpolate target position using the pseudo-random offset
        float local_70 = fVar6 * *(float*)(thisPtr + 0x30) +
                         fVar7 * (globalArray[idx0] * someScale - maxProgress);
        float fStack_6c = fVar6 * *(float*)(thisPtr + 0x34) +
                          fVar7 * (globalArray[idx1] * someScale - maxProgress);
        float fStack_68 = fVar6 * *(float*)(thisPtr + 0x38) +
                          fVar7 * (globalArray[idx2] * someScale - maxProgress);
        float fStack_64 = 0.0f; // unused w component

        if (*(int*)(thisPtr + 0x40) == DAT_0112a8f4) {
            // If blend type matches a specific global, convert quaternion to euler and back
            // outTransform[9] is quaternion y, [8] is x, [10] is z
            FUN_0056b8a0(outTransform[9], outTransform[8], outTransform[10], (undefined1*)local_50);
            FUN_0056de00(&local_70, (undefined1*)local_30, &local_70);
        }

        local_88 = maxProgress; // reset local max
        *(float*)(thisPtr + 0x70) = local_70;
        *(float*)(thisPtr + 0x74) = fStack_6c;
        *(float*)(thisPtr + 0x78) = fStack_68;
        *(float*)(thisPtr + 0x7c) = fStack_64;
        *(float*)(thisPtr + 0x60) = local_80;   // start = 0? Actually local_80 was 0, so start is reset
        *(float*)(thisPtr + 0x64) = fStack_7c;
        *(float*)(thisPtr + 0x68) = fStack_78;
        *(float*)(thisPtr + 0x6C) = fStack_74;

        // Compute delta between target and start
        float deltaX = *(float*)(thisPtr + 0x70) - *(float*)(thisPtr + 0x60);
        float deltaY = *(float*)(thisPtr + 0x74) - *(float*)(thisPtr + 0x64);
        float deltaZ = *(float*)(thisPtr + 0x78) - *(float*)(thisPtr + 0x68);
        float deltaW = *(float*)(thisPtr + 0x7C) - *(float*)(thisPtr + 0x6C);

        // Compute speed as distance / (distance + epsilon)
        float distance = sqrtf(deltaX * deltaX + deltaY * deltaY + deltaZ * deltaZ);
        *(float*)(thisPtr + 0x58) = *(float*)(thisPtr + 0x20) / (distance + *epsilonPtr);
        *progressPtr = 0.0f; // reset progress
    }

    // Advance progress
    float fVar7 = *(float*)(thisPtr + 0x58) * deltaTime + *progressPtr;
    *progressPtr = fVar7;

    float local_84 = 0.0f;
    float* pfVar4;
    if (fVar7 <= local_88) {
        if (0.0f <= fVar7) {
            pfVar4 = progressPtr; // use progress if within [0, max]
        } else {
            pfVar4 = &local_84; // use 0 if negative
        }
    } else {
        pfVar4 = &local_88; // clamp to max
    }
    fVar7 = *pfVar4;
    *progressPtr = fVar7;

    // Interpolate using the clamped progress
    float fVar6 = *(float*)(thisPtr + 0x50);
    // Blend position (x,y,z) from start to target
    float local_70 = anotherZero * 0.0f +
                     fVar6 * ((*(float*)(thisPtr + 0x70) - *(float*)(thisPtr + 0x60)) * fVar7 +
                              *(float*)(thisPtr + 0x60));
    float fStack_6c = anotherZero * 0.0f +
                     fVar6 * ((*(float*)(thisPtr + 0x74) - *(float*)(thisPtr + 0x64)) * fVar7 +
                              *(float*)(thisPtr + 0x64));
    float fStack_68 = anotherZero * local_88 +
                     fVar6 * ((*(float*)(thisPtr + 0x78) - *(float*)(thisPtr + 0x68)) * fVar7 +
                              *(float*)(thisPtr + 0x68));
    float fStack_64 = 0.0f;
    float fStack_74 = 0.0f;
    float fStack_78 = 0.0f;
    float fStack_7c = 0.0f;
    float local_80 = 0.0f;

    // Decompose the blended matrix into position and quaternion
    // local_80/fStack_7c/fStack_78/fStack_74 becomes position (x,y,z,w)
    // local_60/fStack_5c/fStack_58/fStack_54 becomes quaternion (x,y,z,w)
    FUN_00473bc0(&local_80, &local_70, 0, &fStack_5c, &local_60, &fStack_58);

    // Decrease a separate timer (blend fade)
    if (0.0f < *(float*)(thisPtr + 0x2C)) {
        float fVar7 = *(float*)(thisPtr + 0x50) - (deltaTime / *(float*)(thisPtr + 0x2C)) * *(float*)(thisPtr + 0x24);
        *(float*)(thisPtr + 0x50) = fVar7;
        if (fVar7 <= 0.0f) {
            *(float*)(thisPtr + 0x50) = 0.0f;
            *(char*)(thisPtr + 0x8) = 1; // mark blend complete
        }
    }

    // Write output position (xyzw)
    float fVar7_original = outTransform[3];
    outTransform[0] = outTransform[0] + local_80;
    outTransform[1] = outTransform[1] + fStack_7c;
    outTransform[2] = outTransform[2] + fStack_78;
    outTransform[3] = outTransform[3] + fStack_74;
    outTransform[3] = fVar7_original; // w is not updated? Actually it's set back to original value

    // Write output quaternion (xyzw)
    float fVar7_original2 = outTransform[11];
    outTransform[8] = outTransform[8] + local_60;
    outTransform[9] = outTransform[9] + fStack_5c;
    outTransform[10] = outTransform[10] + fStack_58;
    outTransform[11] = outTransform[11] + fStack_54;
    outTransform[11] = fVar7_original2; // w not updated
}