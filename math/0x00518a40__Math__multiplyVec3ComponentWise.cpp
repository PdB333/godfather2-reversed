// FUNC_NAME: Math::multiplyVec3ComponentWise
// Function at 0x00518a40 performs component-wise multiplication of the first three elements of two float4 vectors.
// The result is stored in the output vector's first three components, while its fourth (w) component is preserved unchanged.
// This is often used for scaling the vector part of a homogenous coordinate or for per-component vector operations.

void __fastcall multiplyVec3ComponentWise(float* outVec, const float* inVecA, const float* inVecB)
{
    // Component-wise multiply the first three elements
    outVec[0] = inVecA[0] * inVecB[0];  // x component
    outVec[1] = inVecA[1] * inVecB[1];  // y component
    outVec[2] = inVecA[2] * inVecB[2];  // z component

    // The w component (index 3) is calculated but then overwritten with the original value,
    // effectively leaving it unchanged.
    // (The decompiled shows a temporary store and restore, but the result is the same as no operation.)
}