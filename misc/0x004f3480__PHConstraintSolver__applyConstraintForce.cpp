// FUNC_NAME: PHConstraintSolver::applyConstraintForce
void __fastcall PHConstraintSolver::applyConstraintForce(
    void* pSolver,                     // param_1 (ECX, likely this)
    const float* worldAxis,            // param_2 (float[4])
    const float* relativePosition,     // param_3 (float[4]) - position in body space?
    int pExtraData,                    // param_4 (probably float[3] for scale factors)
    float* outputForce                 // param_5 (float[4]) - accumulated force/torque
)
{
    // Access thread-local storage for the physics world
    // FS:0x2c -> pointer to TLS block, offset 8 -> physics world pointer
    byte* pWorldTLS = (byte*)(*(int*)(*(int*)(__readfsdword(0x2c) + 8)));
    // Add offset from this object (offset 0x10) to get particle data block
    byte* particleData = pWorldTLS + *(int*)((char*)pSolver + 0x10);

    // Early out if particle is disabled (bit0)
    if (*particleData & 1)
        return;

    // Constraint descriptor at EDI+0x24
    byte* constraintDesc = *(byte**)((char*)pSolver + 0x24);

    // Compute relative position from particle to constraint anchor
    float relPos[4];
    relPos[0] = *(float*)(particleData + 0x80) - relativePosition[0];
    relPos[1] = *(float*)(particleData + 0x84) - relativePosition[1];
    relPos[2] = *(float*)(particleData + 0x88) - relativePosition[2];
    relPos[3] = *(float*)(particleData + 0x8C) - relativePosition[3];

    float axis[4]; // Local constraint axis
    switch (constraintDesc[1]) // axis frame selector
    {
    case 0: // Use relative position as axis
        axis[0] = relPos[0];
        axis[1] = relPos[1];
        axis[2] = relPos[2];
        axis[3] = relPos[3];
        break;
    case 1: // Use world space axis
        axis[0] = worldAxis[0];
        axis[1] = worldAxis[1];
        axis[2] = worldAxis[2];
        axis[3] = worldAxis[3];
        break;
    case 2: // Use particle body’s first axis (offset 0x50)
        axis[0] = *(float*)(particleData + 0x50);
        axis[1] = *(float*)(particleData + 0x54);
        axis[2] = *(float*)(particleData + 0x58);
        axis[3] = *(float*)(particleData + 0x5C);
        break;
    case 3: // Use particle body’s second axis (offset 0x60)
        axis[0] = *(float*)(particleData + 0x60);
        axis[1] = *(float*)(particleData + 0x64); // 0x64 = 100 decimal
        axis[2] = *(float*)(particleData + 0x68);
        axis[3] = *(float*)(particleData + 0x6C);
        break;
    case 4: // Use particle body’s third axis (offset 0x70)
        axis[0] = *(float*)(particleData + 0x70);
        axis[1] = *(float*)(particleData + 0x74);
        axis[2] = *(float*)(particleData + 0x78);
        axis[3] = *(float*)(particleData + 0x7C);
        break;
    }

    uint flags = *(uint*)(constraintDesc + 4); // flags at +0x04
    if (flags & 4) // if cross product flag set, compute axis = worldAxis x axis (torque arm?)
    {
        // Cross product: axis = worldAxis × axis (standard vector cross)
        float tmpX = axis[0] * worldAxis[1];
        float tmpY = axis[0] * worldAxis[2];
        float tmpZ = axis[1] * worldAxis[0];
        axis[0] = axis[1] * worldAxis[2] - axis[2] * worldAxis[1];
        axis[1] = axis[2] * worldAxis[0] - tmpY;
        axis[2] = tmpX - tmpZ;
        // axis[3] unchanged (homogeneous coordinate)
    }

    // Normalize the axis and compute its length
    float axisLenSq = axis[0]*axis[0] + axis[1]*axis[1] + axis[2]*axis[2];
    float invLen;
    const float epsilonSq = DAT_00e2cbe0; // small threshold
    if (axisLenSq <= epsilonSq)
        invLen = 0.0f;
    else
        invLen = DAT_00e2b1a4 / sqrtf(axisLenSq); // DAT_00e2b1a4 = 1.0f (or identity scale)

    // Compute error magnitude along the constraint axis
    float error;
    switch (*constraintDesc) // constraint type selector
    {
    case 1:
    case 5: // Type 1 or 5: compute dot product of axis with relative position
        // param_2 is overridden to point to relPos in case 1? Actually code sets param_2 = &local_20; (relPos) then falls through to call
        // This is tricky: in case 1 it sets param_2 to relPos, then case 5 uses that.
        // We'll factor out the common call.
        // The function FUN_004bcfb0 likely computes a particular dot product or length.
        // Probably it's VectorLength of relPos (or dot with something).
        // Given the call with param_2 = relPos, it might return the magnitude of relPos.
        error = FUN_004bcfb0(relPos); // returns some float, likely distance
        break;
    case 2: // Dot product with first axis
        error = *(float*)(particleData + 0x50) * relPos[0] +
                *(float*)(particleData + 0x54) * relPos[1] +
                *(float*)(particleData + 0x58) * relPos[2];
        break;
    case 3: // Dot product with second axis
        error = *(float*)(particleData + 0x60) * relPos[0] +
                *(float*)(particleData + 0x64) * relPos[1] + // +100 = 0x64
                *(float*)(particleData + 0x68) * relPos[2];
        break;
    case 4: // Dot product with third axis
        error = *(float*)(particleData + 0x70) * relPos[0] +
                *(float*)(particleData + 0x74) * relPos[1] +
                *(float*)(particleData + 0x78) * relPos[2];
        break;
    }

    // Subtract the constraint's rest length (offset 0x28 in descriptor)
    error -= *(float*)(constraintDesc + 0x28);
    if (error == 0.0f)
        return;

    // Apply error shaping based on type (puVar2[2])
    float shapedError;
    switch (constraintDesc[2])
    {
    case 0: // square
        shapedError = error * error;
        break;
    case 2: // sqrt
        shapedError = sqrtf(error);
        break;
    case 3: // sqrt then reciprocal (falls through to case 4)
        shapedError = sqrtf(error);
        // intentionally fall through
    case 4: // reciprocal
        if (shapedError != 0.0f) // defensive
            shapedError = DAT_00e2b1a4 / shapedError;
        break;
    case 5: // square then reciprocal
        shapedError = error * error;
        if (shapedError != 0.0f)
            shapedError = DAT_00e2b1a4 / shapedError;
        break;
    }

    // Apply stiffness coefficient (offset 0x24)
    float forceMag = *(float*)(constraintDesc + 0x24) * shapedError;

    // If damping coefficient is non-zero, clamp force magnitude (offset 0x2c)
    float damping = *(float*)(constraintDesc + 0x2c);
    if (damping != 0.0f)
    {
        float maxForce = DAT_00e44564 - damping; // some limit
        if (forceMag < 0.0f)
        {
            if (maxForce > forceMag)
                forceMag = forceMag; // already negative, keep? Actually the code: if (fVar8 < fVar7) then fVar8 = fVar7 etc.
            // The decompiled logic: 
            // fVar1 = *(float*)(puVar2+0x2c);
            // fVar8 = DAT_00e44564 - fVar1;
            // if ((fVar8 < fVar7) && (fVar8 = fVar7, fVar1 <= fVar7)) fVar8 = fVar1;
            // So it clamps between (DAT_00e44564 - damping) and damping.
            float clampLow = DAT_00e44564 - damping;
            float clampHigh = damping;
            if (forceMag < clampLow)
                forceMag = clampLow;
            else if (forceMag > clampHigh)
                forceMag = clampHigh;
        }
        else
        {
            // Positive case handled similarly
            float clampLow = DAT_00e44564 - damping;
            float clampHigh = damping;
            if (forceMag < clampLow)
                forceMag = clampLow;
            else if (forceMag > clampHigh)
                forceMag = clampHigh;
        }
    }

    // Apply scaling from extra data (param_4)
    if (flags & 8)
        forceMag *= *(float*)(pExtraData + 4);
    if (flags & 0x10)
        forceMag *= *(float*)(pExtraData + 8);

    // Accumulate force into output
    outputForce[0] += forceMag * axis[0] * invLen;
    outputForce[1] += forceMag * axis[1] * invLen;
    outputForce[2] += forceMag * axis[2] * invLen;
    outputForce[3] += forceMag * axis[3]; // homogeneous component (no normalization)
}