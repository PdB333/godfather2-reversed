// FUNC_NAME: EARSObject::sanitizeMatrix
// Address: 0x00471020
// Copies the object's 4x4 matrix (offset +0xD0) to an output buffer. If the translation
// vector (offsets +0x134, +0x138, +0x13c) is considered near‑zero using a denormal check,
// the output matrix is orthonormalized in place via a helper function.

extern const float g_epsilon;          // DAT_00e44598
extern const float g_zeroAdjust;       // DAT_00e2b1a4
extern const uint32_t g_denormalMask;  // DAT_00e44680

void __thiscall EARSObject::sanitizeMatrix(const void *this, float *outMatrix) const
{
    float tmp;
    int i;
    float *src = (float *)((uintptr_t)this + 0xD0);

    // Copy 16 floats (64 bytes) – the 4x4 transformation matrix
    for (i = 0; i < 16; i++) {
        outMatrix[i] = src[i];
    }

    // Check the translation vector (3 floats starting at +0x134)
    float comp0 = *(float *)((uintptr_t)this + 0x134);
    float comp1 = *(float *)((uintptr_t)this + 0x138);
    float comp2 = *(float *)((uintptr_t)this + 0x13C);

    // Use integer trick to detect denormals / near‑zero components
    float diff0 = (float)((uint32_t)(comp0 - g_zeroAdjust) & g_denormalMask);
    float diff1 = (float)((uint32_t)(comp1 - g_zeroAdjust) & g_denormalMask);
    float diff2 = (float)((uint32_t)(comp2 - g_zeroAdjust) & g_denormalMask);

    if (g_epsilon < diff0 || g_epsilon < diff1 || g_epsilon < diff2) {
        // One or more components are degenerate → orthonormalize the matrix copy
        orthonormalizeMatrix(outMatrix, outMatrix);
    }
}