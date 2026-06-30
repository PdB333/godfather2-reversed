// FUNC_NAME: normalizeVector
// Function address: 0x004f8820
// Reconstructed: Normalize a 3D vector; source is passed in EAX (custom calling convention), destination via parameter.
// Uses threshold squared to avoid division by zero; scaling factor is 1.0f (normalized length).
// Constants:
//   DAT_00e2cbe0 -> likely a small epsilon squared (e.g., 1e-12)
//   DAT_00e2b1a4 -> 1.0f

void __fastcall normalizeVector(float* outVec)
{
    // Source vector pointer is in EAX (first argument register, custom fastcall)
    float* inVec;
    __asm { mov inVec, eax }  // Explicitly capture EAX for clarity

    float fVar1;
    float fVar2;

    fVar1 = *inVec;
    // Compute squared length
    fVar2 = fVar1 * fVar1 + inVec[1] * inVec[1] + inVec[2] * inVec[2];

    // Check against threshold (tiny epsilon squared)
    if (fVar2 <= DAT_00e2cbe0) {
        fVar2 = 0.0f;
    } else {
        // fVar2 becomes 1.0f / length (assuming DAT_00e2b1a4 == 1.0f)
        fVar2 = DAT_00e2b1a4 / SQRT(fVar2);
    }

    // Scale and store result
    *outVec = fVar1 * fVar2;
    outVec[1] = fVar2 * inVec[1];
    outVec[2] = fVar2 * inVec[2];
    return;
}