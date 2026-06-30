// FUNC_NAME: MathUtils::vecLerp3PreserveW
void __fastcall MathUtils::vecLerp3PreserveW(float* result, float* srcA, float* srcB, float factor) {
    // Save original w component (4th float) of result
    float savedW = result[3];

    // Read components of srcA and srcB
    float ay = srcA[1];
    float az = srcA[2];
    float aw = srcA[3];
    float by = srcB[1];
    float bz = srcB[2];
    float bw = srcB[3];

    // Linearly interpolate all 4 components
    result[0] = factor * srcA[0] + srcB[0];
    result[1] = factor * ay + by;
    result[2] = factor * az + bz;
    result[3] = factor * aw + bw;

    // Restore the original w component (w is not interpolated)
    result[3] = savedW;
}