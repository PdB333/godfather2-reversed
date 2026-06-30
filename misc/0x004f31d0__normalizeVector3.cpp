// FUNC_NAME: normalizeVector3
// Function address: 0x004f31d0
// Role: Normalizes a 3D vector; if squared length <= epsilon, returns zero vector.
// Input: pointer to 3 floats (in EAX), Output: pointer to 3 floats (on stack)

// Threshold constant for zero-length detection (very small value, e.g., ~1e-10)
static const float kNormalizeEpsilon = *(float*)0x00e2cbe0;

// Reciprocal of the square root factor (likely 1.0f)
static const float kInvSqrtFactor = *(float*)0x00e2b1a4;

void __fastcall normalizeVector3(float* in_EAX, float* param_1)
{
    float fVar1;
    float fVar2;

    fVar1 = *in_EAX;
    fVar2 = fVar1 * fVar1 + in_EAX[1] * in_EAX[1] + in_EAX[2] * in_EAX[2];
    if (fVar2 <= kNormalizeEpsilon) {
        fVar2 = 0.0f;
    } else {
        fVar2 = kInvSqrtFactor / __SQRT(fVar2); // 1.0f / length
    }
    *param_1 = fVar1 * fVar2;
    param_1[1] = fVar2 * in_EAX[1];
    param_1[2] = fVar2 * in_EAX[2];
}