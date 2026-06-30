// FUNC_NAME: EARSVector3D::normalizeTo
void EARSVector3D::normalizeTo(float* out) const
{
    // Compute squared length of this vector (offsets: x=+0x00, y=+0x04, z=+0x08)
    float lengthSq = x*x + y*y + z*z;

    // Threshold from DAT_00e2cbe0 (approx 1e-8f, zero length epsilon)
    static const float kZeroEpsilon = 1e-8f; // Original: DAT_00e2cbe0
    // Inverse length multiplier from DAT_00e2b1a4 (1.0f)
    static const float kInvFactor = 1.0f;    // Original: DAT_00e2b1a4

    float scale;
    if (lengthSq <= kZeroEpsilon) {
        scale = 0.0f;
    } else {
        scale = kInvFactor / sqrt(lengthSq);
    }

    out[0] = x * scale;
    out[1] = y * scale;
    out[2] = z * scale;
}