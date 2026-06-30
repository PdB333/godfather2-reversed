// FUNC_NAME: Quaternion::normalize
// Function address: 0x0045c080
// Purpose: Normalizes a 4D vector (quaternion) componentwise.
// If the squared length is <= EPSILON, result is set to zero.
// Otherwise, scale factor = INV_SQRT_EPS (likely 1.0) / sqrt(squaredLength)
// Params: 
//   in ecx? Actually Ghidra shows __fastcall but we treat as thiscall with two float* args.
//   Actually from decompiled: in_EAX (ecx) = source vector, param_1 (stack) = destination.
// We'll reconstruct as: void Quaternion::normalize(float* dest, const float* src);

void __fastcall Quaternion::normalize(float *dest, const float *src)
{
    float fVar1;
    float fVar2;
    
    fVar1 = *src;
    fVar2 = fVar1 * fVar1 + src[1] * src[1] + src[2] * src[2] + src[3] * src[3];
    // DAT_00e2cbe0: epsilon threshold for near-zero length
    if (fVar2 <= DAT_00e2cbe0) {
        fVar2 = 0.0f;
    }
    else {
        // DAT_00e2b1a4: normalization constant (likely 1.0f for unit quaternion)
        fVar2 = DAT_00e2b1a4 / sqrtf(fVar2);
    }
    *dest = fVar1 * fVar2;
    dest[1] = src[1] * fVar2;
    dest[2] = fVar2 * src[2];
    dest[3] = fVar2 * src[3];
}