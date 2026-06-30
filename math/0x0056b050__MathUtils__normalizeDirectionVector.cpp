// FUNC_NAME: MathUtils::normalizeDirectionVector
void __fastcall MathUtils::normalizeDirectionVector(float *this, float *outDir, float *fromPos, float *toPos)
{
    float dx;
    float dy;
    float dz;
    float distSq;
    float invDist;

    // Compute direction vector components
    dz = toPos[2] - fromPos[2];  // +0x08: Z component
    dy = toPos[1] - fromPos[1];  // +0x04: Y component
    dx = toPos[0] - fromPos[0];  // +0x00: X component

    // Calculate squared distance
    distSq = dz * dz + dy * dy + dx * dx;

    // Check against minimum distance threshold (DAT_00e2cbe0)
    if (distSq <= DAT_00e2cbe0) {
        // Too close, zero out direction
        invDist = 0.0f;
    }
    else {
        // Normalize: 1 / sqrt(distSq) * speed factor (DAT_00e2b1a4)
        invDist = DAT_00e2b1a4 / SQRT(distSq);
    }

    // Store normalized direction vector
    outDir[1] = invDist * dy;  // +0x04: Y component
    outDir[0] = invDist * dx;  // +0x00: X component
    outDir[2] = invDist * dz;  // +0x08: Z component
}