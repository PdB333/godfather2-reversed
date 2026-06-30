// FUNC_NAME: MathUtils::vectorReject
// Address: 0x0056de00
// Role: Performs 3D vector rejection (computes component of vec1 perpendicular to vec2).
// Returns 1 if successful (vec2 not zero/denormal), 0 otherwise.
// Output "out" receives the perpendicular component (vec1 - projection onto vec2).
// The 4th component (out[3]) is preserved as vec1[3].
// Uses global float thresholds for zero/denormal detection: DAT_00e44598 (threshold) and DAT_00e44680 (bitmask).

int __cdecl MathUtils::vectorReject(float* vec1, float* vec2, float* out)
{
    float fVar1 = vec2[1];
    float fVar2 = vec2[0];
    float fVar3 = vec2[2];
    float lenSq = fVar2 * fVar2 + fVar1 * fVar1 + fVar3 * fVar3;  // squared length of vec2

    // Check if vec2 is non-zero/non-denormal using bitwise trick
    if (DAT_00e44598 < (float)((uint)lenSq & DAT_00e44680))
    {
        float savedW = out[3];  // preserve original w component

        // Scalar projection dot(vec1,vec2) / dot(vec2,vec2)
        float scalar = (vec1[0] * fVar2 + vec1[1] * fVar1 + vec1[2] * fVar3) / lenSq;

        // Compute vector projection onto vec2
        out[0] = scalar * fVar2;
        out[1] = scalar * fVar1;
        out[2] = scalar * fVar3;
        out[3] = savedW;  // restore w

        // Subtract projection from vec1 to get perpendicular component
        fVar1 = vec1[1];
        fVar2 = vec1[2];
        fVar3 = vec1[3];
        out[0] = vec1[0] - out[0];
        out[1] = fVar1 - out[1];
        out[2] = fVar2 - out[2];
        out[3] = fVar3;  // final w becomes vec1[3] (overwrites savedW)
        return 1;
    }
    else
    {
        out[0] = 0.0f;
        out[1] = 0.0f;
        out[2] = 0.0f;
        out[3] = 0.0f;  // zero all components (decompiler showed duplicate)
        return 0;
    }
}