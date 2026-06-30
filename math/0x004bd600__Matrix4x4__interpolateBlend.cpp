// FUNC_NAME: Matrix4x4::interpolateBlend
void __thiscall Matrix4x4::interpolateBlend(float this[24], float blendA, float blendB)
{
    float df = DAT_00e2eff4; // global time delta or scale factor
    float invLen;

    // Compute first set of basis vectors (indices 4-7) from this[8,11], this[0,3], etc.
    // Looks like displacement or velocity scaled by df, then subtract position offsets.
    float vx = this[0xb] * df - this[8];
    float vy = this[0xf] * df - this[0xc];
    float vz = this[3] * df - this[0];
    float vw = this[7] * df - this[4];
    this[4] = vz; // store temporarily
    this[5] = vw;
    this[6] = vx;
    this[7] = vy;

    // Normalize to unit length using global magnitude (DAT_00e2b1a4)
    invLen = DAT_00e2b1a4 / sqrtf(vz*vz + vw*vw + vx*vx);
    this[4] *= invLen;
    this[5] *= invLen;
    this[6] *= invLen;
    this[7] *= invLen;

    // Second set (indices 8-11) - based on reverse differences
    vx = this[8] - this[0xb];
    vy = this[0xc] - this[0xf];
    vz = this[0] - this[3];
    vw = this[4] - this[7];
    this[8] = vz;
    this[9] = vw;
    this[10] = vx;
    this[11] = vy;

    invLen = DAT_00e2b1a4 / sqrtf(vz*vz + vw*vw + vx*vx);
    this[8] *= invLen;
    this[9] *= invLen;
    this[10] *= invLen;
    this[11] *= invLen;

    // Third set (indices 12-15) - using df again
    vx = this[7] * df - this[5];
    vy = this[0xb] * df - this[9];
    vz = this[3] * df - this[1];
    vw = this[0xf] * df - this[0xd];
    this[12] = vz;
    this[13] = vx;
    this[14] = vy;
    this[15] = vw;

    invLen = DAT_00e2b1a4 / sqrtf(vy*vy + vz*vz + vx*vx);
    this[12] *= invLen;
    this[13] *= invLen;
    this[14] *= invLen;
    this[15] *= invLen;

    // Fourth set (indices 16-19) - reverse of third with df
    vx = this[9] - this[0xb];
    vy = this[0xd] - this[0xf];
    vz = this[1] - this[3];
    vw = this[5] - this[7];
    this[16] = vz;
    this[17] = vw;
    this[18] = vx;
    this[19] = vy;

    invLen = DAT_00e2b1a4 / sqrtf(vz*vz + vw*vw + vx*vx);
    this[16] *= invLen;
    this[17] *= invLen;
    this[18] *= invLen;
    this[19] *= invLen;

    // Fifth set (indices 0-3) - using blendA
    vx = this[7] * blendA - this[6];
    vy = this[0xb] * blendA - this[10];
    vz = this[3] * blendA - this[2];
    vw = this[0xf] * blendA - this[0xe];
    this[0] = vz;
    this[1] = vx;
    this[2] = vy;
    this[3] = vw;

    invLen = DAT_00e2b1a4 / sqrtf(vx*vx + vy*vy + vz*vz);
    this[0] *= invLen;
    this[1] *= invLen;
    this[2] *= invLen;
    this[3] *= invLen;

    // Sixth set (indices 20-23) - using blendB (this appears to be an inverted blend)
    vx = this[6] - this[7] * blendB;
    vy = this[10] - this[0xb] * blendB;
    vz = this[2] - this[3] * blendB;
    vw = this[0xe] - this[0xf] * blendB;
    this[20] = vz;
    this[21] = vx;
    this[22] = vy;
    this[23] = vw;

    invLen = DAT_00e2b1a4 / sqrtf(vz*vz + vx*vx + vy*vy);
    this[20] *= invLen;
    this[21] *= invLen;
    this[22] *= invLen;
    this[23] *= invLen;

    // Final matrix finishing step (likely normalizes or completes the transformation)
    FUN_004bd490();
}