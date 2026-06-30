// FUN_00508d90: MathUtils::normalizeVector
extern float g_epsilonSq; // +0x00e2cbe0
extern float g_targetLength; // +0x00e2b1a4 (typically 1.0f)

// Normalizes a 3D vector (src) into a destination vector (dest) with a fixed target length.
// Sets dest to zero if the squared length of src is <= g_epsilonSq.
void __fastcall MathUtils::normalizeVector(float *dest, const float *src) {
    float lenSq = src[0] * src[0] + src[1] * src[1] + src[2] * src[2];
    float scale;
    if (lenSq <= g_epsilonSq) {
        scale = 0.0f;
    } else {
        scale = g_targetLength / sqrt(lenSq);
    }
    dest[0] = src[0] * scale;
    dest[1] = src[1] * scale;
    dest[2] = src[2] * scale;
}