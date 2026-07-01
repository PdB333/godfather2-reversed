// FUNC_NAME: SmoothInterpolator::updateSmoothTransform
uint SmoothInterpolator::updateSmoothTransform(float* pResult, uint64* pTarget, float* pSource, float timeStep, float blendFactor)
{
    // DAT_00e445ac: scaling/lerp factor (probably 1.0f or frame time)
    // DAT_00e44598: lower bound for pTarget value (as float)
    // DAT_00e446d8: upper bound for pTarget value
    // DAT_00e44564: decay constant (e.g., 1.0f - smoothing factor)

    float fTemp;
    uint64* puTarget = pTarget;
    float* pfSource = pSource;

    // Interpret pTarget as double and split into two 32-bit floats
    uint64 targetVal = *pTarget;
    float targetLow  = (float)(targetVal & 0xFFFFFFFF);
    float targetHigh = (float)(targetVal >> 32);

    uint64 local24; // reinterpreted as two floats
    float local1c;  // third component of target (from pTarget[1] high?)

    local24 = CONCAT44(pfSource[1] * DAT_00e445ac + targetHigh,
                       pfSource[0] * DAT_00e445ac + targetLow);
    local1c = pfSource[2] * DAT_00e445ac + *(float*)(pTarget + 1); // pTarget[1] low 32 bits?

    FUN_005e7ba0(&pSource, 0);           // zero out pSource pointer? (likely a set operation)
    FUN_005e7a40(pSource, local_c);      // extract some transform from pSource into local_c (12-byte buffer)
    uint result = FUN_004a09b0(local_c, puTarget, &local24, &pTarget); // compute something and possibly update pTarget

    // Check if the result magnitude is below the current smoothing factor and within bounds
    if ((extraout_ST0 < (float10)pResult[6]) && (DAT_00e44598 < (float)pTarget) && ((float)pTarget < DAT_00e446d8))
    {
        float vecOut[3];
        FUN_0043a210(&vecOut[0], pfSource);   // compute some vector from source (e.g., direction or scale)

        pResult[6] = (float)extraout_ST0;       // update smoothing factor
        *(uint64*)(pResult + 7) = local24;      // store interpolated target (offset +28)
        pResult[9] = local1c;                   // store third component (offset +36)

        // Recompute with pTarget treated as float (address cast)
        float pTargetFloat = *(float*)&pTarget; // dubious: treat pointer as float
        float targetLow2  = *(float*)puTarget;  // low 32 of target as float? (same as before)
        float targetHigh2 = (float)((ulonglong)*puTarget >> 32);

        float fVar1, fVar5;
        local24 = CONCAT44(pfSource[1] * pTargetFloat + targetHigh2,
                           pfSource[0] * pTargetFloat + targetLow2);
        fVar1 = pfSource[2];
        *(uint64*)pResult = local24;                    // store initial part (offset +0)
        *(uint64*)(pResult + 3) = local24;              // duplicate (offset +12)
        float decay = DAT_00e44564 - timeStep;
        fVar5 = fVar1 * pTargetFloat + *(float*)(puTarget + 1);
        pResult[2] = fVar5;                             // store intermediate (offset +8)

        // Blend first set of output coordinates (offset +0..+8) using decay and vecOut
        *pResult       = vecOut[0] * decay + pResult[0];
        pResult[1]     = vecOut[1] * decay + pResult[1];
        pResult[5]     = fVar5;                         // overwrite offset +20? (confusing assignment)
        pResult[2]     = vecOut[2] * decay + pResult[2];

        // Blend second set of output coordinates (offset +12..+20) using blendFactor
        pResult[3]     = vecOut[0] * blendFactor + pResult[3];
        pResult[4]     = vecOut[1] * blendFactor + pResult[4];
        pResult[5]     = vecOut[2] * blendFactor + pResult[5];

        // Return success flag (1) encoded with part of fVar5
        return CONCAT31((int3)((uint)fVar5 >> 8), 1);
    }
    return result & 0xFFFFFF00; // clear low byte (failure indicator)
}