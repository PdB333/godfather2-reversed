// FUNC_NAME: Math::scaleVector3ToLength
// Function at 0x004f5a70: Scales a 3D vector to a specified length (typically 1.0) with zero-vector protection.
// Uses global constants: g_normalizeThresholdSq (0x00e2cbe0) and g_targetLength (0x00e2b1a4).

void __fastcall Math::scaleVector3ToLength(const float* src, float* dst)
{
    // Source and destination pointers: src in ECX, dst in EDX (fastcall)
    float lenSq = src[0] * src[0] + src[1] * src[1] + src[2] * src[2];
    float scale;

    if (lenSq <= *(float*)0x00e2cbe0) {
        // Near-zero vector: output zero
        scale = 0.0f;
    } else {
        // Scale to target length (e.g., 1.0 for normalization)
        scale = *(float*)0x00e2b1a4 / sqrtf(lenSq);
    }

    dst[0] = src[0] * scale;
    dst[1] = src[1] * scale;
    dst[2] = src[2] * scale;
}