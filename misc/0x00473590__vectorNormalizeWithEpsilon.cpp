// FUNC_NAME: vectorNormalizeWithEpsilon
//
// Function at 0x00473590: Normalizes a 3D vector to a specific magnitude (DAT_00e2b1a4)
// If the squared length is <= DAT_00e2cbe0 (epsilon), output is set to zero vector.
// Calling convention: __fastcall, ECX = input pointer, EDX = output pointer.

void __fastcall vectorNormalizeWithEpsilon(float *outVec, float *inVec)
{
    float lengthSq;
    float scale;

    // Compute squared length of input vector
    lengthSq = inVec[0] * inVec[0] + inVec[1] * inVec[1] + inVec[2] * inVec[2];

    // If squared length is below epsilon, treat as zero to avoid division by zero
    // DAT_00e2cbe0 is likely a very small epsilon (e.g., 1e-6)
    if (lengthSq <= DAT_00e2cbe0) {
        scale = 0.0f;
    }
    else {
        // Scale factor: target magnitude / actual length
        // DAT_00e2b1a4 is the desired magnitude (commonly 1.0, but could be other value)
        scale = DAT_00e2b1a4 / SQRT(lengthSq);
    }

    // Write scaled components to output vector
    outVec[0] = inVec[0] * scale;
    outVec[1] = inVec[1] * scale;
    outVec[2] = inVec[2] * scale;
}