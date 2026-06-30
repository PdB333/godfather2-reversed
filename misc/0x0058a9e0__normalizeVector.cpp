// FUNC_NAME: normalizeVector
void __fastcall normalizeVector(float *dst) {
    float *src = reinterpret_cast<float*>(_EAX); // Input vector passed in EAX (fastcall)
    float vx = src[0];
    float vy = src[1];
    float vz = src[2];
    float sqLen = vx*vx + vy*vy + vz*vz;

    // Epsilon threshold to avoid division by zero / normalize zero vectors
    const float epsilon = *reinterpret_cast<const float*>(0x00e2cbe0); // small epsilon value
    const float one = *reinterpret_cast<const float*>(0x00e2b1a4);     // 1.0f

    float scale = 0.0f;
    if (sqLen > epsilon) {
        scale = one / __fastsqrt(sqLen); // sqrt is fast intrinsic in EARS engine
    }

    dst[0] = vx * scale;
    dst[1] = vy * scale;
    dst[2] = vz * scale;
}