// FUNC_NAME: smoothInterpolateVector4
// Address: 0x006d1890
// Performs a smooth interpolation of a 4-component float vector from src to dest,
// using a global smoothing factor. Interpolation is only applied if a condition
// (likely vector equality with tolerance) fails. Returns 1 if interpolation was
// performed, 0 otherwise.

extern float g_smoothFactor; // _DAT_00d5780c

// Internal check: returns non-zero if vectors are considered equal (within tolerance),
// zero if interpolation should proceed.
int checkVectorEquality(const float* src, const float* dest, const float* tolerance);

int smoothInterpolateVector4(float* dest, const float* src)
{
    float factor = g_smoothFactor;
    float tolerance = factor; // The global factor is also used as tolerance for the equality check

    int equal = checkVectorEquality(src, dest, &tolerance);
    if (equal == 0) {
        float srcY = src[1];
        float srcZ = src[2];
        float srcW = src[3];

        dest[0] = (dest[0] - src[0]) * factor + src[0];
        dest[1] = (dest[1] - srcY) * factor + srcY;
        dest[2] = (dest[2] - srcZ) * factor + srcZ;
        dest[3] = (dest[3] - srcW) * factor + srcW;

        return 1;
    }
    return 0;
}