// FUNC_NAME: MathUtils::calcPitchAngle
float calcPitchAngle(const float* vec) {
    // Mask to extract absolute value (likely 0x7FFFFFFF)
    const uint32_t absMask = 0x7FFFFFFF; // DAT_00e44680
    // Threshold to ignore small vectors
    const float threshold = 0.0001f; // DAT_00d5ef84 (example value)

    // Check if all components are below threshold in absolute value
    if (((float)(*(uint32_t*)&vec[0] & absMask) < threshold) &&
        ((float)(*(uint32_t*)&vec[1] & absMask) < threshold) &&
        ((float)(*(uint32_t*)&vec[2] & absMask) < threshold)) {
        return 0.0f;
    }

    // Compute pitch angle: atan2(y, sqrt(x^2 + z^2))
    float x = vec[0];
    float y = vec[1];
    float z = vec[2];
    float horizDist = sqrtf(x * x + z * z);
    return atan2f(y, horizDist);
}