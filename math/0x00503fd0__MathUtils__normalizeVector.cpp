// FUNC_NAME: MathUtils::normalizeVector
void __fastcall normalizeVector(float *outVec, float *inVec) // inVec passed in EAX, outVec in ECX (based on decompiler)
{
    float fVar1;
    float fVar2;

    fVar1 = *inVec;
    // Compute squared length of input vector
    fVar2 = (fVar1 * fVar1) + (inVec[1] * inVec[1]) + (inVec[2] * inVec[2]);

    // If squared length is <= epsilon, treat as zero vector (set fVar2 = 0)
    if (fVar2 <= DAT_00e2cbe0) {  // epsilon threshold (likely 1e-15f)
        fVar2 = 0.0f;
    }
    else {
        // fVar2 = desiredLength / sqrt(squaredLength)
        fVar2 = DAT_00e2b1a4 / sqrtf(fVar2); // desired length (likely 1.0f for unit vector)
    }

    // Scale input components and store to output vector
    *outVec      = fVar1 * fVar2;
    outVec[1]    = fVar2 * inVec[1];
    outVec[2]    = fVar2 * inVec[2];

    return;
}