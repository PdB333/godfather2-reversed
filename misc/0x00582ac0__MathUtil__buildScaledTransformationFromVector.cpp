// FUNC_NAME: MathUtil::buildScaledTransformationFromVector
// Address: 0x00582ac0
// This function computes a scaled transformation (quaternion + translation + scale) from a given vector (likely a quaternion or plane equation).
// It uses global constants g_globalConst1 and g_globalConst2, and a temporary structure obtained from getTempStruct().

extern float g_globalConst1; // DAT_00e44564
extern float g_globalConst2; // DAT_00e2b1a4

// Returns a 64-bit value: low 32 bits = pointer to output, high 32 bits = pointer to source (with stored quaternion and translation)
extern unsigned long long getTempStruct();

void __fastcall buildScaledTransformationFromVector(int unusedParam, float *vec)
{
    float sumSq = vec[0]*vec[0] + vec[1]*vec[1] + vec[2]*vec[2] + vec[3]*vec[3];
    float scale = g_globalConst1 - (g_globalConst2 / sumSq);

    unsigned long long result = getTempStruct();
    float *out = (float *)(result & 0xFFFFFFFF);
    unsigned char *src = (unsigned char *)(result >> 32); // source pointer (offsets 0x0c,0x10,0x14,0x18)

    // Build quaternion: modify scalar part then scale all
    out[3] = g_globalConst1 - *(float *)(src + 0x0c);
    out[0] = scale * out[0];
    out[1] = scale * out[1];
    out[2] = scale * out[2];
    out[3] = scale * out[3];

    // Build translation (negated relative to source)
    out[4] = g_globalConst1 - *(float *)(src + 0x10);
    out[5] = g_globalConst1 - *(float *)(src + 0x14);
    out[6] = g_globalConst1 - *(float *)(src + 0x18);

    // Set last element to constant
    out[7] = g_globalConst2;
}